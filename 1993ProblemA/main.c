#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FILENAME "input.txt"
#define MAX 10
#define PI 3.141596

typedef struct {
    int x;
    int y;
}
point;

typedef struct vertex {
    int label;
    point loc;
    int num_conns;
    point *conns;
    double *slopes;
    int *border_traversed;
}
Vertex;

typedef struct edge {
    int code;
    point vert1;
    point vert2;
}
Edge;

int num,pos=0,set=1;
Vertex *vertices;
Edge *edges;
int i,j,k;
point temp1,temp2;
FILE *inp;

int x1temp;
int y1temp;
int x2temp;
int y2temp;

point make_point(int x, int y) {
    point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

Edge make_edge(int x1, int y1, int x2, int y2) {
    Edge temp;
    temp.vert1.x=x1;
    temp.vert1.y=y1;
    temp.vert2.x=x2;
    temp.vert2.y=y2;
    return temp;
}

int not_in_list(Vertex *list, point a, int max) {
    int i;
    for(i=0;(list[i].loc.x!=a.x || list[i].loc.y!=a.y) && i<max;i++);
    if(max==0 || max==i) return 1;
    return 0;
}

int get_label(Vertex *list, point a,int max) {
    int i;
    for(i=0;i<max;i++) if(list[i].loc.x==a.x
    && list[i].loc.y==a.y) return list[i].label;
    return -1;
}

double get_slope(point a,point b) {
    int x1=a.x,y1=a.y,x2=b.x,y2=b.y;
    if(x2-x1 != 0) {
    /* First quadrant */
    if(x2-x1>0 && y2-y1>0) return atan( ((y2-y1) / (x2-x1)) );
    /* Second quadrant */
    else if(x2-x1<0 && y2-y1>0) return PI-atan(abs( ((y2-y1) / (x2-x1)) ));
    /* Third quadrant */
    else if(x2-x1<0 && y2-y1<0) return PI+atan(abs( ((y2-y1) / (x2-x1)) ));
    /* Fourth quadrant */
    else if(x2-x1>0 && y2-y1<0) return (2*PI)-atan(abs( ((y2-y1) / (x2-x1)) ));
    /* Case where it lies on x-axis */
    else if(x2-x1>0) return 0.0;
    else return PI;
}
    /* Case where it lies on y-axis */
    else if(y2-y1 > 0) return PI/2;
    else return 3*(PI/2);
}

int find_left_turn(Vertex *list, int vertex,
int invertex, double inslope, int pos) {
    int maxlabel=-1,i;
    double max=0.0,adj_angle;
    for(i=0;i<list[vertex].num_conns;i++) {
        if(inslope>PI) {
            adj_angle=list[vertex].slopes[i]-(inslope-PI);
            if(adj_angle<0) adj_angle=(2*PI+adj_angle);
            if( adj_angle>=max
            && invertex!=get_label(list,list[vertex].conns[i],pos) ) {
            maxlabel=get_label(list,list[vertex].conns[i],pos);
            max=adj_angle;
            }
        }
        else if(inslope<PI) {
        adj_angle=list[vertex].slopes[i]+(PI-inslope);
        if( adj_angle>=(2*PI) ) adj_angle=(adj_angle-(2*PI));
        if( adj_angle>=max
            && invertex!=get_label(list,list[vertex].conns[i],pos) ) {
            maxlabel=get_label(list,list[vertex].conns[i],pos);
            max=adj_angle;
            }
        }
        else {
            if(list[vertex].slopes[i]>=max
            && invertex!=get_label(list,list[vertex].conns[i],pos) ) {
            maxlabel=get_label(list,list[vertex].conns[i],pos);
            max=list[vertex].slopes[i];
            }
        }
    }
    return maxlabel;
}

int follow_border(Vertex *list,int vertex,int pos) {
    int i,j;
    int label;
    int prior=0;
    double min=2*PI;
    for(i=0;i<list[vertex].num_conns && prior!=4;i++) {
        if(list[vertex].slopes[i]==0.0
        && list[vertex].border_traversed[i]!=1){
            label = get_label(list,list[vertex].conns[i],pos);
            prior=3;
        }
        else if(list[vertex].slopes[i]==PI/2
        && list[vertex].border_traversed[i]!=1 && prior!=3) {
        label = get_label(list,list[vertex].conns[i],pos);
        prior=2;
        }
        else if(list[vertex].slopes[i]==PI
        && list[vertex].border_traversed[i]!=1 && prior!=2) {
        label = get_label(list,list[vertex].conns[i],pos);
        prior=1;
        }
        else if(list[vertex].slopes[i]==(3*PI/2)
        && list[vertex].border_traversed[i]!=1 && prior!=1) {
        label = get_label(list,list[vertex].conns[i],pos);
        }
    }
    for(i=0;i<list[label].num_conns;i++) {
        if(list[label].conns[i].x==list[vertex].loc.x
        && list[label].conns[i].y==list[vertex].loc.y) {
        list[label].border_traversed[i]=1;
        }
    }
    return label;
}


int main(){
    if((inp=fopen(FILENAME,"r"))==NULL) exit(1);
    fscanf(inp,"%d",&num);
    while(num!=0) {
        printf("Data set #%d\n",set);
        vertices=malloc( num*sizeof(Vertex) );
        edges=malloc( num*sizeof(Edge) );
        for(i=0;i<num;i++) vertices[i].loc=make_point(-1,-1);
        pos=0;
        /* Read-in data and fill the edges and vertices arrays */
        for(i=0;i<num;i++) {
            fscanf(inp,"%d %d %d %d",&x1temp,&y1temp,&x2temp,&y2temp);
            temp1=make_point(x1temp,y1temp);
            temp2=make_point(x2temp,y2temp);
            if(not_in_list(vertices,temp1,pos)) {
                vertices[pos].loc=make_point(x1temp,y1temp);
                vertices[pos].label=pos;
                vertices[pos].num_conns=0;
                vertices[pos].conns=malloc(MAX * sizeof(point));
                for(j=0;j<MAX;j++) {
                    vertices[pos].conns[j].x=-1;
                    vertices[pos].conns[j].y=-1;
                }
                vertices[pos].slopes=malloc(MAX * sizeof(double));
                vertices[pos].border_traversed=malloc(MAX * sizeof(double));
                for(j=0;j<MAX;j++) vertices[pos].slopes[j]=PI/2;
                pos++;
            }
            if(not_in_list(vertices,temp2,pos)) {
                vertices[pos].loc=make_point(x2temp,y2temp);
                vertices[pos].label=pos;
                vertices[pos].num_conns=0;
                vertices[pos].conns=malloc(MAX * sizeof(point));

            for(j=0;j<MAX;j++) {
                vertices[pos].conns[j].x=-1;
                vertices[pos].conns[j].y=-1;
            }
            vertices[pos].slopes=malloc(MAX * sizeof(double));
            vertices[pos].border_traversed=malloc(MAX * sizeof(double));
            for(j=0;j<MAX;j++) vertices[pos].slopes[j]= PI/2;
            pos++;
            }
            edges[i]=make_edge(x1temp,y1temp,x2temp,y2temp);
        }
        /* Fill the conns & slopes elements */
        for(i=0;i<num;i++) {
            for(j=0;j<num;j++) {
                if(edges[i].vert1.x==vertices[j].loc.x
                && edges[i].vert1.y==vertices[j].loc.y) {
                    vertices[j].conns[vertices[j].num_conns]=
                    make_point(edges[i].vert2.x,edges[i].vert2.y);
                    vertices[j].slopes[vertices[j].num_conns]=
                    get_slope(vertices[j].loc,edges[i].vert2);
                    vertices[j].border_traversed[vertices[j].num_conns]=0;
                    (vertices[j].num_conns)++;
                }
                if(edges[i].vert2.x==vertices[j].loc.x
                && edges[i].vert2.y==vertices[j].loc.y) {
                        vertices[j].conns[vertices[j].num_conns]=
                        make_point(edges[i].vert1.x,edges[i].vert1.y);
                        vertices[j].slopes[vertices[j].num_conns]=
                        get_slope(vertices[j].loc,edges[i].vert1);
                        vertices[j].border_traversed[vertices[j].num_conns]=0;
                        (vertices[j].num_conns)++;
                }
            }
        }
        fscanf(inp,"%d",&num);
        free(vertices);
        free(edges);
        set++;
    }
    fclose(inp);
    return 0;
}






