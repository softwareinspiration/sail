/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2020 Dmitry Baryshev

    The MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>

#include "sail-common.h"

sail_status_t sail_alloc_meta_entry_node(struct sail_meta_entry_node **node) {

    SAIL_CHECK_META_ENTRY_NODE_PTR(node);

    void *ptr;
    SAIL_TRY(sail_malloc(&ptr, sizeof(struct sail_meta_entry_node)));
    *node = ptr;

    (*node)->key   = NULL;
    (*node)->value = NULL;
    (*node)->next  = NULL;

    return SAIL_OK;
}

void sail_destroy_meta_entry_node(struct sail_meta_entry_node *node) {

    if (node == NULL) {
        return;
    }

    sail_free(node->key);
    sail_free(node->value);
    sail_free(node);
}

sail_status_t sail_copy_meta_entry_node(struct sail_meta_entry_node *source, struct sail_meta_entry_node **target) {

    SAIL_CHECK_META_ENTRY_NODE_PTR(source);
    SAIL_CHECK_META_ENTRY_NODE_PTR(target);

    SAIL_TRY(sail_alloc_meta_entry_node(target));

    SAIL_TRY_OR_CLEANUP(sail_strdup(source->key, &(*target)->key),
                        /* cleanup */ sail_destroy_meta_entry_node(*target));
    SAIL_TRY_OR_CLEANUP(sail_strdup(source->value, &(*target)->value),
                        /* cleanup */ sail_destroy_meta_entry_node(*target));

    return SAIL_OK;
}

void sail_destroy_meta_entry_node_chain(struct sail_meta_entry_node *node) {

    while (node != NULL) {
        struct sail_meta_entry_node *node_next = node->next;

        sail_destroy_meta_entry_node(node);

        node = node_next;
    }
}

sail_status_t sail_copy_meta_entry_node_chain(struct sail_meta_entry_node *source, struct sail_meta_entry_node **target) {

    SAIL_CHECK_META_ENTRY_NODE_PTR(target);

    if (source == NULL) {
        *target = NULL;
        return SAIL_OK;
    }

    *target = NULL;
    struct sail_meta_entry_node *meta_entry_node_current = NULL;

    while (source != NULL) {
        struct sail_meta_entry_node *meta_entry_node = NULL;

        SAIL_TRY_OR_CLEANUP(sail_copy_meta_entry_node(source, &meta_entry_node),
                            /* cleanup */sail_destroy_meta_entry_node_chain(*target));

        if (*target == NULL) {
            *target = meta_entry_node;
            meta_entry_node_current = *target;
        } else {
            meta_entry_node_current->next = meta_entry_node;
            meta_entry_node_current = meta_entry_node_current->next;
        }

        source = source->next;
    }

    return SAIL_OK;
}
