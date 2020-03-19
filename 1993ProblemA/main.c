#include <stdio.h>
#include <stdlib.h>
#define FICHIER "input.txt"

int n;
int i,j,k,set=1;
double tot_dist,capacite,mpg,cout;
double** dist;
double* prix;
FILE *fp;


double cout_minimal(int n, double capacite,double mpg, double cout, double* prix, double** dist) {
    int i,j,k,s,l=0,chk=n+1, examine=1;
    double min;
    double temp;
    double** val;
    double* w;
    w=malloc((n+2)*sizeof(double));
    val=malloc((n+2)*sizeof(double));
    for(i=0; i<n+2; i++) {
        val[i]=malloc((n+2)*sizeof(double));
    }

    double* T;
    T=malloc((n+2)*sizeof(double));

    return (cout + w[n+1]/100.0);
}


int main()
{
    if((fp=fopen(FICHIER,"r"))==NULL) exit(1);
    fscanf(fp, "%lf", &tot_dist);
        while(tot_dist!=-1.0) {
            fscanf(fp, "%lf %lf %lf %d", &capacite, &mpg, &cout, &n);
            dist=malloc((n+2)*sizeof(double));
            for(i=0;i<n+2;i++) {
                dist[i]=malloc((n+2)*sizeof(double));
            }
            prix=malloc((n+2)*sizeof(double));

            for(i=0;i<n+2;i++) {
                for(j=0;j<n+2;j++) {
                    dist[i][j]=0.0;
                }
            }
            prix[0] = cout/100.0;
            prix[n+1] = 0.0;
            for(j=1;j<n+1;j++) {
                fscanf(fp, "%lf %lf",&dist[0][j], &prix[j]);
            }
            dist[0][n+1] = tot_dist;
            for(k=0;k<n+2;k++) {
                for(j=k+1;j<n+2;j++) {
                    dist[k][j] = dist[0][j]-dist[0][k];
                }
            }
            printf("Donnees #%d\n", set);
            printf(" Le prix minimal est de %.2lf\n\n",
            cout_minimal(n, capacite, mpg, cout, prix, dist));
            fscanf(fp, "%lf", &tot_dist);
            set++;
        }
        fclose(fp);
        return 0;
}
