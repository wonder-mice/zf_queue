#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <zf_queue.h>

struct line_entry
{
    const char *value;
    zf_tailq_node node_c;
    zf_tailq_node node_cpp;
    zf_tailq_node node_mixed;
};

struct line_storage
{
    zf_tailq_head lines_c;
    zf_tailq_head_<line_entry, &line_entry::node_cpp> lines_cpp;
    // Declaration below can be used in headers that are included by both
    // C and C++ source files
    zf_tailq_head_t(line_entry, node_mixed) lines_mixed;
};

int main(int argc, char *argv[])
{
    line_storage storage;
    // 1. initialize
    storage.lines_c = ZF_TAILQ_INITIALIZER(&storage.lines_c);
    storage.lines_cpp = ZF_TAILQ_INITIALIZER(&storage.lines_c);
    storage.lines_mixed = ZF_TAILQ_INITIALIZER(&storage.lines_c);
    // ... or ...
    zf_tailq_init(&storage.lines_c);
    zf_tailq_init(&storage.lines_cpp);
    zf_tailq_init(&storage.lines_mixed);
    // 2. populate
    for (int i = 0; argc > i; ++i)
    {
        line_entry *const entry = (line_entry *)malloc(sizeof(line_entry));
        entry->value = argv[i];
        zf_tailq_insert_head(&storage.lines_c, &entry->node_c);
        zf_tailq_insert_head_(&storage.lines_cpp, entry);
        zf_tailq_insert_head_(&storage.lines_mixed, entry);
    }
    // 3. iterate
    while (!zf_tailq_empty(&storage.lines_c) &&
           !zf_tailq_empty(&storage.lines_cpp) &&
           !zf_tailq_empty(&storage.lines_mixed))
    {
        // 4. get entry
        line_entry *const entry_c =
                zf_entry(zf_tailq_last(&storage.lines_c), line_entry, node_c);
        line_entry *const entry_cpp =
                zf_tailq_last_(&storage.lines_cpp);
        line_entry *const entry_mixed =
                zf_tailq_last_(&storage.lines_mixed);
        // 5. access value
        printf("c:     \"%s\"\n", entry_c->value);
        printf("cpp:   \"%s\"\n", entry_cpp->value);
        printf("mixed: \"%s\"\n", entry_mixed->value);
        // 6. remove
        zf_tailq_remove(&storage.lines_c, &entry_c->node_c);
        zf_tailq_remove_(&storage.lines_cpp, entry_cpp);
        zf_tailq_remove_(&storage.lines_mixed, entry_mixed);
        assert(entry_c == entry_cpp && entry_c == entry_mixed);
        free(entry_mixed);
        printf("----\n");
    }
    return 0;
}
