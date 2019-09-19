#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"


struct person employees[100];

int readEmployees(int type,int silent){
    //0 attendance
    //1 salary
    //2 totalsalary
    //3 name
    //4 all
    printf("Read Employee \n");

    FILE *infile;
    struct person input;

    // Open person.dat for reading
    infile = fopen ("database", "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        return 0;
    }

    // read file contents till end of file
    int idx = 0;
    while(fread(&input, sizeof(struct person), 1, infile)){
        employees[idx] = input;
        idx++;

        if(!silent){
            switch (type){
                case 0:
                    printf ("name = %s  attendance = %d  \n",input.name,input.attendance);
                    break;
                case 1:
                    printf ("name = %s  salary per day = %d  \n", input.name,input.salaryperday);
                    break;
                case 2:
                    printf ("name = %s  total salary = %d \n", input.name,input.totalsalary);
                    break;
                case 3:
                    printf (" name = %s \n",
                            input.name);
                    break;
                default:
                    printf (" name = %s attendance = %d salary per day = %d , total salary = %d \n",
                            input.name, input.attendance, input.salaryperday, input.totalsalary);
                    break;
            }

        }

    }


    // close file
    fclose (infile);
    if(!silent){
        printf("Press [Enter] key to continue.\n");
        while(getchar()!='\n');
        getchar();
    }


    return 0;
}

int addEmployee(){

    printf("Update Employee \n");


    FILE *fp;
    FILE *fp_tmp;
    int found=0;
    struct person myrecord;

    fp=fopen("database", "r");
    if (!fp) {
        printf("Unable to open file database");
    }
    fp_tmp=fopen("tmp", "w");
    if (!fp_tmp) {
        printf("Unable to open file temp file.");
        return -1;
    }

    char name[25];
    printf("Enter Employee Name(Below 20 letters):");
    scanf("%s",name);
    struct person newrec = {"",myrecord.attendance,myrecord.salaryperday,myrecord.totalsalary};

    strcpy(newrec.name , name);

    if(fp){
        while (fread(&myrecord,sizeof(struct person),1,fp) != NULL) {

            fwrite(&myrecord, sizeof(struct person), 1, fp_tmp);

        }
        fclose(fp);
    }


    fwrite(&newrec, sizeof(struct person), 1, fp_tmp);
    printf("The New Record Added.\n\n");

    fclose(fp_tmp);

    remove("database");
    rename("tmp", "database");

    readEmployees(3,0);


//    FILE *outfile;
//
//    // open file for writing
//    outfile = fopen ("database", "w");
//    if (outfile == NULL)
//    {
//        fprintf(stderr, "\nError opend file\n");
//        exit (1);
//    }
//
//    char name[25];
//    printf("Enter Employee Name(Below 20 letters):");
//    scanf("%s",name);
//    struct person input1 = {"",0,0,0};
//    input1.salaryperday = 0;
//    input1.attendance = 0;
//    input1.totalsalary = 0;
//    strcpy(input1.name , name);
//
//    fwrite (&input1, sizeof(struct person), 1, outfile);
//
//    int res = -1;
//    if(fwrite != 0){
//        printf("contents to file written successfully !\n");
//        res = 1;
//    }else{
//        printf("error writing file !\n");
//    }
//
//    fclose (outfile);
//    readEmployees();
    return 0;
}

int removeEmployee(){
    printf("Remove Employee \n");

    char searchname[20];
    printf("Enter Existing Employee Name to Dalete:");
    scanf("%s",searchname);
    FILE *fp;
    FILE *fp_tmp;
    int found=0;
    struct person myrecord;

    fp=fopen("database", "r");
    if (!fp) {
        printf("Unable to open file database");
        return -1;
    }
    fp_tmp=fopen("tmp", "w");
    if (!fp_tmp) {
        printf("Unable to open file temp file.");
        return -1;
    }

    while (fread(&myrecord,sizeof(struct person),1,fp) != NULL) {
        if (strcmp (searchname, myrecord.name) == 0) {

            printf("A record with requested name found and deleted.\n\n");
            found=1;

        } else {
            fwrite(&myrecord, sizeof(struct person), 1, fp_tmp);
        }
    }
    if (! found) {
        printf("No record(s) found with the requested name: %s\n\n", searchname);
    }

    fclose(fp);
    fclose(fp_tmp);

    remove("database");
    rename("tmp", "database");

    readEmployees(3,0);
}

int updateEmployee(){
    printf("Update Employee \n");

    char searchname[20];
    printf("Enter Existing Employee Name to update:");
    scanf("%s",searchname);
    FILE *fp;
    FILE *fp_tmp;
    int found=0;
    struct person myrecord;

    fp=fopen("database", "r");
    if (!fp) {
        printf("Unable to open file database");
        return -1;
    }
    fp_tmp=fopen("tmp", "w");
    if (!fp_tmp) {
        printf("Unable to open file temp file.");
        return -1;
    }

    while (fread(&myrecord,sizeof(struct person),1,fp) != NULL) {
        if (strcmp (searchname, myrecord.name) == 0) {
            char name[25];
            printf("Enter Employee Name(Below 20 letters):");
            scanf("%s",name);
            struct person newrec = {"",myrecord.attendance,myrecord.salaryperday,myrecord.totalsalary};

            strcpy(newrec.name , name);

            fwrite(&newrec, sizeof(struct person), 1, fp_tmp);
            printf("A record with requested name found and updated.\n\n");
            found=1;

        } else {
            fwrite(&myrecord, sizeof(struct person), 1, fp_tmp);
        }
    }
    if (! found) {
        printf("No record(s) found with the requested name: %s\n\n", searchname);
    }

    fclose(fp);
    fclose(fp_tmp);

    remove("database");
    rename("tmp", "database");

    readEmployees(3,0);
    return 0;

}

int updateEmployeedata(int type, int isDelete){
    //0 attendance
    //1 salary
    //2 totalsalary

    printf("Update Employee \n");

    int searchname[20];
    printf("Enter Existing Employee Name to update:");
    scanf("%s",searchname);
    FILE *fp;
    FILE *fp_tmp;
    int found=0;
    struct person myrecord;

    fp=fopen("database", "r");
    if (!fp) {
        printf("Unable to open file database");
        return -1;
    }
    fp_tmp=fopen("tmp", "w");
    if (!fp_tmp) {
        printf("Unable to open file temp file.");
        return -1;
    }

    while (fread(&myrecord,sizeof(struct person),1,fp) != NULL) {
        if (strcmp (searchname, myrecord.name) == 0) {
            int value;


            if(type == 0){
                if(isDelete){
                    value = 0;
                }else{
                    printf("Enter Attendance Data of Employee %s",searchname);
                    scanf("%d",&value);
                }

                struct person newrec = {"",myrecord.attendance,myrecord.salaryperday,myrecord.totalsalary};
                strcpy(newrec.name , myrecord.name);
                newrec.attendance = value;
                fwrite(&newrec, sizeof(struct person), 1, fp_tmp);

            }else if(type == 1){
                if(isDelete){
                    value = 0;
                }else{
                printf("Enter Salary Per Day of Employee %s",searchname);
                scanf("%d",&value);
                }
                struct person newrec = {"",myrecord.attendance,myrecord.salaryperday,myrecord.totalsalary};
                strcpy(newrec.name , myrecord.name);
                newrec.salaryperday = value;
                fwrite(&newrec, sizeof(struct person), 1, fp_tmp);

            }else if(type == 2){
                if(isDelete){
                    value = 0;
                }else {
                    printf("Enter Total Salary of Employee %s", searchname);
                    scanf("%d", &value);
                }
                struct person newrec = {"",myrecord.attendance,myrecord.salaryperday,myrecord.totalsalary};
                strcpy(newrec.name , myrecord.name);
                newrec.totalsalary = value;
                fwrite(&newrec, sizeof(struct person), 1, fp_tmp);

            }



            printf("A record with requested name found and updated.\n\n");
            found=1;

        } else {
            fwrite(&myrecord, sizeof(struct person), 1, fp_tmp);
        }
    }
    if (! found) {
        printf("No record(s) found with the requested name: %s\n\n", searchname);
    }

    fclose(fp);
    fclose(fp_tmp);

    remove("database");
    rename("tmp", "database");

    readEmployees(type,0);
    return 0;

}

int calculateTotalSalary(){
    printf("Update Employee \n");


    FILE *fp;
    FILE *fp_tmp;
    struct person myrecord;

    fp=fopen("database", "r");
    if (!fp) {
        printf("Unable to open file database");
        return -1;
    }
    fp_tmp=fopen("tmp", "w");
    if (!fp_tmp) {
        printf("Unable to open file temp file.");
        return -1;
    }

    while (fread(&myrecord,sizeof(struct person),1,fp) != NULL) {
        int tot = myrecord.salaryperday * myrecord.attendance;
        struct person newrec = {"",myrecord.attendance,myrecord.salaryperday,myrecord.totalsalary};
        strcpy(newrec.name , myrecord.name);
        newrec.totalsalary = tot;
        fwrite(&newrec, sizeof(struct person), 1, fp_tmp);

        printf("Successfully Calculated the total salaries\n\n");

    }


    fclose(fp);
    fclose(fp_tmp);

    remove("database");
    rename("tmp", "database");

    readEmployees(2,0);
    return 0;
}





int main() {
    printf("Getting Ready...\n");
    readEmployees(4,1);
    printf("Ready !\n");

    int ign;
    char ch;

    while (1){

        if(ch !='\n'){
            printf("--------------MAIN MENU----------------\n");

            printf("1. Login as HR \n");
            printf("2. Login as Accountant\n");
            printf("q. Exit\n");

        }
        scanf("%c", &ch);
        char chsub;
        int res;
        switch(ch){
            case '1':


                while(1){
                    if(chsub !='\n'){
                        printf("--------------HR ACTIONS MENU----------------\n");
                        printf("1. Add new Employees \n");
                        printf("2. Update Employee Name \n");
                        printf("3. Delete Employee \n");
                        printf("4. Add Employee Attendance \n");
                        printf("5. Update Employee Attendance\n");
                        printf("6. Delete Employee Attendance\n");
                        printf("7. Add Employee Salary \n");
                        printf("8. Update Employee Salary\n");
                        printf("9. Delete Employee Salary\n");
                        printf("0. View Employee Salary Total \n");
                        printf("x. Go Back \n");
                    }

                    scanf ("%c", &chsub);
                    if(chsub == 'x'){
                        break;
                    }
                    switch(chsub){
                        case '1':
                            addEmployee();
                            break;
                        case '2':
                            updateEmployee();
                            break;
                        case '3':
                            removeEmployee();
                            break;
                        case '4':
                            updateEmployeedata(0,0);
                            break;
                        case '5':
                            updateEmployeedata(0,0);
                            break;
                        case '6':
                            updateEmployeedata(0,1);
                            break;
                        case '7':
                            updateEmployeedata(1,0);
                            break;
                        case '8':
                            updateEmployeedata(1,0);
                            break;
                        case '9':
                            updateEmployeedata(1,1);
                            break;
                        case '0':
                            readEmployees(2,0);

                            break;
                        case 'x':
                            break;
                        case '\n': break;
                        default:
                            printf("Invalid input %c", chsub);
                            break;
                    }

                }
                printf("---------------HR END---------------\n");
                break;
            case '2':


                while(1){
                    if(chsub !='\n'){
                        printf("--------------ACCOUNTANT ACTIONS MENU----------------\n");
                        printf("1. View Employees \n");
                        printf("2. View Employee Attendance \n");
                        printf("3. View Employee Salary Per Day \n");
                        printf("4. Calculate Total Salary \n");
                        printf("5. Add Total Salary \n");
                        printf("6. Edit Total Salary \n");
                        printf("7. Delete Total Salary \n");
                        printf("x. Go Back \n");
                    }
                    scanf ("%c", &chsub);
                    if(chsub == 'x'){
                        break;
                    }
                    switch(chsub){
                        case '1':
                            readEmployees(3,0);
                            break;
                        case '2':
                            readEmployees(0,0);
                            break;
                        case '3':
                            readEmployees(1,0);
                            break;
                        case '4':
                            calculateTotalSalary();
                            break;
                        case '5':
                            updateEmployeedata(2,0);
                            break;
                        case '6':
                            updateEmployeedata(2,0);
                            break;
                        case '7':
                            updateEmployeedata(2,1);
                            break;
                        case 'x':
                            break;
                        case '\n': break;
                        default:
                            printf("Invalid input %c", chsub);
                            break;
                    }
                }
                printf("--------------ACC END----------------\n");
                break;
            case 'q':
                printf("Exiting");
                exit(0);
                break;
            case '\n': break;
            default:
                printf("Invalid input Character %c", ch);
        }
    }
    return 0;
}