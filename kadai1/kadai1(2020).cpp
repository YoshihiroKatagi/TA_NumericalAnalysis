#include<stdio.h>
​
#define E 1.0          // Young's modules
#define alpha 1.0      // Coefficient of linear expansion
#define dT 1.0         // 100K 
​
​
struct Variable
{
    /* data */
    double A1;              // cross section 1
    double A2;              // cross section 2
    double L1;              // length 1
    double L2;              // lwngth 2
    double sigma1;          // thermal stress 1
    double sigma2;          // thermal stress 2
    double delta1;          // elongation 1
    double delta2;          // elongation 2
};
​
// B)'s answer
////////////////////////////////////////////////////////////////////////////
void calc(Variable *Var)
{
    double A1 = Var->A1, A2 = Var->A2, L1 = Var->L1, L2 = Var->L2;
​
    Var->sigma1 = -1.0 * alpha * dT * E * A2 * (L1 + L2)
                / (A1 * L2 + A2 * L1);
    
    Var->sigma2 = -1.0 * alpha * dT * E * A1 * (L1 + L2)
                / (A1 * L2 + A2 * L1);
                
    Var->delta1 = L1 * L2 * (A1 - A2) / (A1 * L2 + A2 * L1);
​
    Var->delta2 = L1 * L2 * (A2 - A1) / (A1 * L2 + A2 * L1);
}
/////////////////////////////////////////////////////////////////////////////
​
// plot dat file
// void plot_dat(char* FileName, char labelName[5][7])
// {   
// ​
//     FILE* gp;
// ​
//     for(int i=1; i<5; i++)
//     {
//         gp = _popen("gnuplot", "w");
//         if(gp == NULL)
//         {
//             printf("cannot open gnuplot.");
//         }
// ​
//         fprintf(gp, "unset key\n");                                             // deleate legend
//         fprintf(gp, "set title '%s'\n", labelName[i]);                              // set title
//         fprintf(gp, "set xlabel '%s'\n", labelName[0]);                             // set xlabel
//         fprintf(gp, "set ylabel '%s'\n", labelName[i]);                             // set ylabel
//         fprintf(gp, "set ytics 0.1\n");                                         // set tics 0.1
//         fprintf(gp, "set terminal png\n");                                      //save graph as png
//         fprintf(gp, "set output 'result_%s_%s.png'\n", labelName[0], labelName[i]);
//         fprintf(gp, "plot '%s' using 1:%d with lines\n",FileName, i+1);
//         fprintf(gp, "set terminal windows\n");
//         fprintf(gp, "set output\n");
//         _pclose(gp);
//     }
// }
​
void calc_changeA1(void)
{
    double A1_min = 0.5, A1_max = 1.5, h = 0.001;
    int N = (int) (A1_max - A1_min) / h;
    Variable Var = 
    {
        A1_min, 0.5, 1.0, 1.0, 0, 0, 0, 0 
    };
​
    //make FILE as result_changeA1.csv
    char *FileName = "result_changeA1.dat";
    FILE *fp = fopen(FileName, "w");
​
    for (int i=0; i < N+1; i++)
    {
        calc(&Var);
​
        fprintf(fp, "%f %f %f %f %f\n", Var.A1, Var.sigma1, Var.sigma2, Var.delta1, Var.delta2);
​
        Var.A1 += h;
​
    }
​
    fclose(fp);
​
    //So that I can set graph's label easily, I made a char labelName[5][7] that stores label name.
    char labelName[5][7] = {"A1", "sigma1", "sigma2", "delta1", "delta2"};
    // plot_dat(FileName, labelName);
​
}
​
void calc_changeL1(void)
{
    double L1_min = 0.5, L1_max =1.5, h = 0.001;
    int N = (int) (L1_max - L1_min) / h;
    Variable Var =
    {
        1.0, 0.5, L1_min, 1.0, 0, 0, 0, 0
    };
​
    char *FileName = "result_changeL1.dat";
    FILE *fp =fopen(FileName, "w");
​
    for(int i=0; i<N+1; i++)
    {
        calc(&Var);
​
        fprintf(fp, "%f %f %f %f %f\n", Var.L1, Var.sigma1, Var.sigma2, Var.delta1, Var.delta2);
​
        Var.L1 += h;
    }
​
    fclose(fp);
​
    char labelName[5][7] = { "L1", "sigma1", "sigma2", "delta1", "delta2"};
    // plot_dat(FileName, labelName);
}
​
​
​
int main(void)
{
    calc_changeA1();
    calc_changeL1();
​
    return 0;
    
}