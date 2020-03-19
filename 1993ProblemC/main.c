#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct le_node {
    int anc_capacity;
    int desc_capacity;
    int desc_count;
    int anc_count;
    int index;
    int *weight;
    struct le_node **anc, **desc;
    char *name;
}
NODE;

NODE *make_node(char *name){
    int i;
    NODE *node;
    node = calloc(1, sizeof(NODE));
    node->name = malloc(6*sizeof(char));
    for(i=0;i<6;i++) node->name[i]=name[i];
    NODE **desc;
    desc = calloc(5, sizeof(NODE));
    node->desc=desc;
    NODE **anc;
    anc = calloc(5, sizeof(NODE));
    node->anc = anc;
    node->desc_count = 0;
    node->anc_count=0;
    node->anc_capacity=5;
    node->desc_capacity=5;
    node->weight=calloc(node->anc_capacity,sizeof(int));
    for(i=0;i<node->anc_capacity;i++) node->weight[i]=0;
    return node;
}

void free_node(NODE *p) {
    int i;
    free(p->name);
    for(i=0;i<p->desc_count;i++) {
        free(p->desc[i]);
    }
    free(p->desc);
    for(i=0;i<p->anc_count;i++) {
        free(p->anc[i]);
    }
    free(p->anc);
    free(p->weight);
    free(p);
}

void update_anc_capacity(NODE *p) {
    NODE **anc;
    int *weight;
    anc = realloc(anc,p->anc_capacity+1);
    p->anc = anc;
    ++p->anc_capacity;
    weight=realloc(weight,p->anc_capacity);
    p->weight=weight;
}

void update_desc_capacity(NODE *p) {
    NODE **desc;
    desc = calloc(p->desc_capacity+1, sizeof(NODE));
    p->desc = desc;
    ++p->desc_capacity;
}

void sort_out_node(NODE *p, NODE *q, int rel) {
    if(q->desc_count>=q->desc_capacity) update_desc_capacity(q);
    else {
    q->desc[q->desc_count] = calloc(1, sizeof(NODE));
    q->desc[q->desc_count] = p;
    ++q->desc_count;
    }
    if(p->anc_count>=p->anc_capacity) update_anc_capacity(p);
    else {
    p->anc[p->anc_count] = calloc(1, sizeof(NODE));
    p->anc[p->anc_count] = q;
    ++p->anc_count;
    }
    p->weight[p->anc_count-1]=rel;
}

void collect_anc(NODE *p, int *marked, int index) {
    int i;
    int v[index];
    for(i=0;i<index;i++) v[i]=-1;
    if(p->anc_count == 0) return;
    if(p==NULL || v[p->index]>=0) return;
    else {
        for(i=0;i<p->anc_count;i++) {
            marked[p->anc[i]->index] = p->weight[i] + marked[p->index];
            ++v[p->index];
            collect_anc(p->anc[i], marked, index);
        }
    }
}

void find_LCA(NODE *p, NODE *q, int index, int *m, int *n, int *LCA) {
    int least = 1000001, i;
    int *pmarked = malloc(index*sizeof(int));
    int *qmarked = malloc(index*sizeof(int));
    for(i=0;i<index;i++) pmarked[i] = qmarked[i]=-1;
    *LCA=-1;
    pmarked[p->index]=0;
    qmarked[q->index]=0;
    collect_anc(p, pmarked, index);
    collect_anc(q, qmarked, index);
    for(i=0; i< index; i++) {
        if(pmarked[i]>=0 && qmarked[i]>=0 && (pmarked[i]+qmarked[i] < least)) {
            least =pmarked[i]+qmarked[i];
            *LCA = i;
        }
    }
    if((*LCA)>-1) {
        if(pmarked[(*LCA)]<=qmarked[(*LCA)]) {
            *m=pmarked[(*LCA)] -1;
            *n=qmarked[(*LCA)] - (*m)- 1;
        }
        else {
            *m=qmarked[(*LCA)] -1;
            *n=pmarked[(*LCA)] - (*m)- 1;
        }
    }
    free(pmarked);
    free(qmarked);
}




int main() {
    char c;
    char *name1, *name2;
    char buffer[100];
    int rel, index=0, i, j,quit1, quit2, node_count=0;
    int n1, n2, LCA, m,n;
    NODE **nodes;
    nodes=calloc(10000, sizeof(NODE));
    name1=malloc(6*sizeof(char));
    name2=malloc(6*sizeof(char));
    NODE *node1;
    node1=calloc(1, sizeof(NODE));
    NODE *node2;
    node2=calloc(1, sizeof(NODE));
    while((c=getchar())!='E') {
        switch(c) {
            case 'R':
            if(scanf("%5s %5s %d", name1, name2, &rel)!=3) {
                exit(1);
            }
            j=quit1 =quit2=0;
            while(j<index && (quit1<1 || quit2<1)) {
                if(strcmp(name1, nodes[j]->name)==0) {
                    *node1 = *(nodes[j]);
                    n1=j;
                    ++quit1;
                }
                if(strcmp(name2, nodes[j]->name)==0) {
                *node2 = *(nodes[j]);
                n2=j;
                ++quit2;
                }
                ++j;
            }
            if(quit1==0) {
                node1 = make_node(name1);
                nodes[index] = calloc(1, sizeof(NODE));
                *nodes[index] =*node1;
                nodes[index]->index = index;
                n1=index;
                ++index;
            }
            if(quit2==0) {
                node2 =make_node(name2);
                nodes[index] = calloc(1, sizeof(NODE));
                *nodes[index] =*node2;
                nodes[index]->index = index;
                n2=index;
                ++index;
            }
            sort_out_node(nodes[n1], nodes[n2], rel);
            fgets(buffer, 100, stdin);
            break;
            case 'F':
            if(scanf("%5s %5s", name1, name2)!=2) {
                exit(1);
            }
            j=quit1 =quit2=0;
            while(j<index && (quit1<1 || quit2<1)) {
                if(strcmp(name1, nodes[j]->name)==0) {
                    *node1 = *(nodes[j]);
                    ++quit1;
                }
                if(strcmp(name2, nodes[j]->name)==0) {
                    *node2 = *(nodes[j]);
                    ++quit2;
                }
                ++j;
            }
            if(quit1+quit2==2) {
                find_LCA(node1, node2, index, &m ,&n, &LCA);
                if(LCA==-1)
                printf("%s and %s are not related.\n", node1->name, node2->name);
                else if(LCA == node2->index)
                printf("%s and %s are descendant-%d\n", node1->name, node2->name, n);
                else if(LCA == node1->index)
                printf("%s and %s are descendant-%d\n", node1->name, node2->name, n);
                else {
                    printf("%s and %s are cousin-%d-%d\n", node1->name, node2->name, m, n);
                }
            }
            else printf("%s and %s are not related.\n", name1, name2);
            fgets(buffer, 100, stdin);
            break;
            case '#':
            fgets(buffer, 100, stdin);
            break;
        }
    }
    for(j=0;j<node_count;j++) free_node(nodes[j]);
    free(nodes);
    free_node(node1);
    free_node(node2);
    free(name1);
    free(name2);
    return 0;
}
