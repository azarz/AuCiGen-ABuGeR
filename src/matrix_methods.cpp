void invert_matrix(double mat[3][3],double M[3][3])
{
    int i, j;
    double determinant = 0;

    //finding determinant
    for(i = 0; i < 3; i++)
        determinant = determinant + (mat[0][i] * (mat[1][(i+1)%3] * mat[2][(i+2)%3] - mat[1][(i+2)%3] * mat[2][(i+1)%3]));

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++)
            M[i][j] = ((mat[(j+1)%3][(i+1)%3] * mat[(j+2)%3][(i+2)%3]) - (mat[(j+1)%3][(i+2)%3] * mat[(j+2)%3][(i+1)%3]))/ determinant;
    }
}
void matrix_product(double MG[3][3],double MD[3][1], double MR[3][1])
{
    MR[0][0] = MG[0][0]*MD[0][0] + MG[0][1]*MD[1][0] + MG[0][2]*MD[2][0];
    MR[1][0] = MG[1][0]*MD[0][0] + MG[1][1]*MD[1][0] + MG[1][2]*MD[2][0];
    MR[2][0] = MG[2][0]*MD[0][0] + MG[2][1]*MD[1][0] + MG[2][2]*MD[2][0];
}
void matrix_translation(double T[3][1],double S[3][1],double St[3][1])
{
    St[0][0] = S[0][0]+T[0][0];
    St[1][0] = S[1][0]+T[1][0];
    St[2][0] = S[2][0]+T[2][0];
}
