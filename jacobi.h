//
// Created by TuanAnh on 8/27/2021.
//

#ifndef MYGAUSS_JACOBI_H
#define MYGAUSS_JACOBI_H

float T[10],ATJ[10][10],BTJ[10];

//Hàm kiểm tra tính chéo trội của ma trận
int checkCheoTroi(int n){
    int check;
    bool cheoTroiHang = false, cheoTroiCot = false;
    float checkHang = 0, checkCot = 0;

    // Kiểm tra chéo trội hàng
    for (int i = 1; i <= n; ++i) {
        checkHang = 0;
        for (int j = 1; j <=n ; ++j) {
            if (j != i){
                checkHang = checkHang + fabs(A[i][j]);
            }
        }
        if (fabs(A[i][i]) > checkHang){
            cheoTroiHang = true;
        } else cheoTroiHang = false;
    }

    // Kiểm tra chéo trội cột
    for (int i = 1; i <=n ; ++i) {
        checkCot = 0;
        for (int j = 1; j <= n; ++j) {
            if (j != i){
                checkCot = checkCot + fabs(A[j][i]);
            }
        }
        if (fabs(A[i][i]) > checkCot){
            cheoTroiCot = true;
        } else cheoTroiCot = false;
    }

    if (cheoTroiCot == true){
        if (cheoTroiHang == true){
            check = 3;
        }
        if (cheoTroiHang == false){
            check = 2;
        }
    }
    if (cheoTroiCot == false){
        if (cheoTroiHang == true){
            check = 1;
        }
        if (cheoTroiHang == false){
            check = 0;
        }
    }
    return check;
}

void cheoTroiHang(int n){
    float temp[10][10],sum;
    for (int i = 1; i <= n; ++i) {
        T[i] = 1 / A[i][i];
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            temp[i][j] = A[i][j] * T[i];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j == i){
                ATJ[i][j] = 1 - temp[i][j];
            }
            if (j != i){
                ATJ[i][j] = - temp[i][j];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        BTJ[i] = B[i] * T[i];
    }

}
void jacobi(int check){
    float nMC,saiSo,XC[10],XC1[10],temp;
    int nMI = 0;
    if (check == 1){
        printf("Ma tran he so cheo troi hang \n");
        cheoTroiHang(n);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                AC[i][j] = ATJ[i][j];
            }
        }
        for (int i = 1; i <= n; ++i) {
            BS[i] = BTJ[i];
        }
        for (int i = 1; i <= 3; ++i) {
            nMC = getNormMatrix(i);
            if (nMC < 1){
                nMI = i;
                break;
            }
        }
        temp = getNormMatrix(nMI) / (1 - getNormMatrix(nMI));
        for (int i = 1; i <= n; ++i) {
            XC[i] = BS[i];
        }
        saiSo = temp;
        while (saiSo >= esl){
            for (int i = 1; i <= n; ++i) {
                XC1[i] = 0;
                for (int j = 1; j <= n; ++j) {
                    XC1[i] = XC1[i] + AC[i][j] * XC[j];
                }
                XC1[i] = XC1[i] + BS[i];
            }
            for (int i = 1; i <= n; ++i) {
                XI[i] = XC1[i] - XC[i];
            }
            for (int i = 1; i <= n; ++i) {
                XC[i] = XC1[i];
            }
            saiSo = temp * getNormVector(nMI);
            for (int i = 1; i <= n; ++i) {
                printf("X[%d] = %f\n",i,XC1[i]);
            }
            printf("-======================================-\n");

        }
        for (int i = 1; i <= n; ++i) {
            X[i] = XC1[i];
        }
    }
    if (check == 2){

    }
}
#endif //MYGAUSS_JACOBI_H
