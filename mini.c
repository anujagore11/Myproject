/*****************************************************************************
 * Copyright (C) Anuja K. Gore anujgore11@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int printmenu() {
	system("clear");
	int ch;
	printf("\n\n\n\n\n");
	printf("\t\t\t\t\t----------------------------\n");
	printf("\t\t\t\t\tEMPLOYEE RECORDS MANAGEMENT\n");
	printf("\t\t\t\t\t----------------------------\n\n");
	printf("\t\t\t\t\t[1].Add record of new employee\n");
	printf("\t\t\t\t\t[2].Show records\n");
	printf("\t\t\t\t\t[3].Search a record\n");
	printf("\t\t\t\t\t[4].Delete a record\n");
	printf("\t\t\t\t\t[5].Modify a record\n");
	printf("\t\t\t\t\t[6].Show salary slip\n");
	printf("\t\t\t\t\t[7].Exit\n");
	printf("\n\n\t\t\t\t\tEnter ur choice :");
	scanf("%d", &ch);
	return ch;
}
int main(){
	typedef struct dob {
		int dd;
		int mm;
		int yy;
	} date;

	typedef struct employee {
		char name[20];
		int basic;
		int pday;
		int id;
		char dep[20];
		date b, j;
	}emp;
	enum cases {A, B};
	int choice, i, l1, l2, p, b, dd, mm, yy, id1, flag = 0;
	long sal;
	emp e;
	char nxt, name[20], ch, dep[20], c,d;
	FILE *fp, *fn, *ft,*fx; 
	
	while(1) {
	fp = fopen("file.txt", "rb+");
	if(fp == NULL){
		fp = fopen("file.txt","wb+");
		if(fp == NULL){
			printf("Cannot create file");
			exit(1);
		}
	}
	else{
		fp = fopen("file.txt","ab+");
		if(fp == NULL){
			printf("Cannot OPEN file");
			exit(1);
		}
	}
	choice = printmenu();
	switch(choice) {
		case 1:
		/***adding info of new employee***/
			system("clear");
			do {
				printf("\nEnter emp name:");
				fflush(stdin);
				scanf("%s", e.name);
				l1 = strlen(e.name);
				e.name[l1] =  '\0';
				printf("\nEnter date of birth of emp:");
				scanf("%d%d%d", &e.b.dd, &e.b.mm, &e.b.yy);
				printf("\nEnter emp basic salary:");
				scanf("%d", &e.basic);
				printf("\nEnter present days of emp:");
				scanf("%d", &e.pday);
				printf("\nEnter emp id:");
				scanf("%d", &e.id);
				printf("\nEnter date of joining:");
				scanf("%d%d%d", &e.j.dd, &e.j.mm, &e.j.yy);
				printf("Enter department:");
				scanf("%s", e.dep);
				l2 = strlen(e.dep);
				e.dep[l2] =  '\0';
				fwrite(&e, sizeof(e), 1, fp);
				printf("\nDo u want to add another record?: y/n\n");
				fflush(stdin);
				scanf("%s", &ch);
	 		} while(ch == 'y');
			fclose(fp);
			break;
		case 2:
			/***display***/
			system("clear");
			printf("\n\n");
			printf("\t\tDisplay options:\n");
			printf("\t\t\t[A]View All\n");
			printf("\t\t\t[B]View Department wise\n");
			printf("\n\t\tEnter your choice:");
			scanf("%s", &ch);
			switch(ch) {
				case 'A': /**Display all records**/
					system("clear");
					fseek(fp, 0, SEEK_SET); //this moves file cursor to start of the file
					printf("--------------------------------------------------------------------\n");
					printf("ID\tName\t DOB\tbasic salary\tPresent Days\tDepartment\tJoin Date\n");
					printf("--------------------------------------------------------------------\n");
					// read the file and fetch the record one record per fetch
					while(fread(&e, sizeof(e), 1, fp) == 1) { 	
				   		printf("%d\t", e.id);
						printf("%s\t", e.name);
						printf("%d/%d/%d\t", e.b.dd, e.b.mm, e.b.yy);
						printf("%d\t\t", e.basic);
						printf("%d\t", e.pday);
						printf("%s\t", e.dep);
						printf("%d/%d/%d\n", e.j.dd, e.j.mm, e.j.yy);	
					}
					scanf("%c", &c);
					if(c == 'e')
						break;
					break;

				case 'B':/**Display Departmentwise**/
					system("clear");
					printf("\tEnter department:");
					scanf("%s", dep);
					printf("============ %s DEPARTMENT===========\n", dep);
					fseek(fp, 0, SEEK_SET); /*this moves file cursor to start of the file*/
					printf("---------------------------------------------------------------------\n");
					printf("ID\tName\t DOB\tbasic salary\tPresent Days\tJoining Date\n");
					printf("---------------------------------------------------------------------\n");

					/*read the file and fetch the record one record per fetch*/
					while(fread(&e, sizeof(e), 1, fp) == 1) { 
						if(strcmp(e.dep, dep) == 0) {	
					   		printf("%d\t", e.id);
							printf("%s\t", e.name);
							printf("%d/%d/%d\t", e.b.dd, e.b.mm, e.b.yy);
							printf("%d\t\t", e.basic);
							printf("%d\t", e.pday);
							printf("%d/%d/%d\n", e.j.dd, e.j.mm, e.j.yy);	
						}
					}
					scanf("%c", &c);
					if(c == 'e')
						break;
					break;
			}
			printf("\nGo to main menu-Press y : ");
			scanf("%c", &c);
				break;
			break;
		case 3:
			/***search the record***/
			system("clear");
			printf("\t\tSearch Options\n");
			printf("\t\t\t1. Search by name\n");
			printf("\t\t\t2. Search by id\n");
			printf("\t\t\t3. Search by Department\n");
			printf("\t\t\t4.Search by joining date\n");
			printf("\n\t\tEnter your choice:");
			scanf("%d", &i);
			switch(i) {
				case 1:/***Search by name***/
					system("clear");
					printf("-------Search Employee By Name-------\n");
					printf("Enter employee Name:\n");
     					scanf("%s",name);
					rewind(fp);
					while(fread(&e, sizeof(e), 1, fp)!=0) {
						if(strcmp(e.name, name) == 0) {
							printf("Record found:\n\n");
							printf("ID:%d\nName:%s\nDOB:%d/%d/%d\nBasic salary:%d\nPresent days:%d\nJoin Date:%d/%d/%d\n\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
							flag = 1;
							break;
						}
					}
					fclose(fp);
					if(flag == 0) 
						printf("Record not found\n");
					scanf("%c", &c);
						break;		
					break;
				case 2:/***Search by id***/
					system("clear");
					printf("---------Search Employee By Id---------\n");
					printf("Enter the emp id: ");
					scanf("%d", &id1);
					rewind(fp);
					while(fread(&e, sizeof(e), 1, fp) == 1) {
						if(e.id == id1) {
							printf("Record found:\n\n");
							printf("ID:%d\nName:%s\nDOB:%d/%d/%d\nBasic salary:%d\nPresent days:%d\nJoin Date:%d/%d/%d\n\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
							flag = 1;
							break;
						}
					}
					fclose(fp);
					if(flag == 0)
						printf("\nRecord not found");
					scanf("%c", &c);	
						break;			
					break;
				case 3:/****Search by Department****/
					system("clear");
					printf("-------Search Employee By Department-------\n");
					printf("Enter Department:\n");
     					scanf("%s",dep);
					rewind(fp);
					while(fread(&e, sizeof(e), 1, fp)!=0) {
						if(strcmp(e.dep, dep) == 0) {
							printf("Record found:\n\n");
							printf("ID:%d\nName:%s\tDOB:%d/%d/%d\nBasic salary:%d\nPresent days:%d\nJoin Date:%d/%d/%d\n\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
							flag = 1;
							break;
						}
					}
					fclose(fp);
					if(flag == 0) 
						printf("Record not found\n");
					scanf("%c", &c);
						break;	
					break;
				case 4:/***Search by joining date***/
					system("clear");
					printf("---------Search Employee By Id----------\n");
					printf("Enter the date: ");
					scanf("%d%d%d", &dd, &mm, &yy);
					rewind(fp);
					while(fread(&e, sizeof(e), 1, fp) == 1) {
						if(dd == e.j.dd && mm == e.j.mm && yy == e.j.yy) {
							printf("Record found:\n\n");
							printf("ID:%d\nName:%s\nDOB:%d/%d/%d\nBasic  salary:%d\tPresent days:%d\nJoin Date:%d/%d/%d\n\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
							flag = 1;
							break;
						}
					}
					fclose(fp);
					if(flag == 0)
						printf("\nRecord not found");
					scanf("%c", &c);
						break;		
					break;
				 
			}
			printf("Go to main menu-Press y : \n");
			scanf("%c", &c);	
				break;	
			break;

		case 4:
			/***delete***/
			system("clear");
			printf("Enter emp id to delete:");
			scanf("%d", &id1);
			ft = fopen("temp.txt", "ab+");
			fn = fopen("abc.txt", "wb+");
			while(fread(&e, sizeof(e), 1, fp) == 1) {
				if(e.id == id1) {
					fwrite(&e, sizeof(e), 1 , ft);
					flag = 1;
				}
				else
				fwrite(&e, sizeof(e), 1 , fn);
			}
			fclose(fp);
			fclose(fn);
			remove("file.txt");
			rename("abc.txt", "file.txt");
			if(flag == 0)
				printf("Record not found\n");
			else 
				printf("Record is deleted\n");

			printf("Go to main menu-Press y : ");
			scanf("%c", &c);	
			//if(c == 'e'){
///printf("ddddf");
///				break;}	
			break;

		case 5:
			/***Modify the record***/
			system("clear");
			printf("Enter the employee name to modify:\n");
			scanf("%s", name);
			
			fx = fopen("file.txt", "rb+");
			while(fread(&e, sizeof(e), 1, fx) == 1) { /* fetch all record from file*/
                        	if(strcmp(e.name, name) == 0) { /*if entered name matches with that in file*/
					printf("Existing record:\n");
                            		printf("ID:%d\tName:%s\tDOB:%d/%d/%d\tbasic  salary:%d\tpresent days:%d\tJoin Date:%d/%d/%d\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);

					printf("Update basic  salary: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter new basic  salary:");
						scanf("%d", &e.basic);
					}
					printf("Update present days: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter present days:");
						scanf("%d", &e.pday);
					}
					printf("Update name: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter modified name:");
						scanf("%s", e.name);
					}
					printf("Update DOB: y / n? :");
					scanf("%s", &ch);
					if(ch == 'y') {
						printf("Enter modified date:");
						scanf("%d%d%d", &e.b.dd, &e.b.mm, &e.b.yy);
					}
					/* move the cursor 1 step back from current position*/
                            		fseek(fx, -(sizeof(e)),SEEK_CUR); 
					/*overwrite the record*/
                            		fwrite(&e, (sizeof(e)), 1, fx); 
					flag = 1;
					break;
                        	}
			}
			if(flag == 0)
				printf("Record not found\n");
			else{
				printf("Record is Updated\n");
				printf("ID:%d\tName:%s\tDOB:%d/%d/%d\tbasic salary:%d\tpresent days:%d\tJoin Date:%d/%d/%d\n", e.id, e.name, e.b.dd, e.b.mm, e.b.yy, e.basic, e.pday, e.j.dd, e.j.mm, e.j.yy);
			}
			fclose(fx);
			fclose(fp);
			printf("\nGo to main menu-press y");
			scanf("%c", &d);
				break;
			break;

		case 6:
			/*calculate salary slip*/
			system("clear");
			printf("Enter ID of d emp: ");
			scanf("%d", &id1);
			while(fread(&e, sizeof(e), 1, fp) == 1) {
				if(id1 == e.id) {
					p = e.pday;
					b = e.basic;
					sal = p * b;
					flag = 1;
					break;
				}
			}
			if(flag == 1) {
				printf("\n");
				printf("Department:%s\n", e.dep);
				printf("Salary Details:\n");
				printf("ID:%d\nName:%s\nBasic:%d\nPresent Days:%d\nNet Salary:%lu\n\n", e.id, e.name, e.basic, e.pday, sal);
			}
			fclose(fp);
			printf("Go to main menu-Press y:\n");
			scanf("%c", &c);	
				break;	
			break;
			
		case 7:
			/*Exit*/
			exit(0);
			break;

		default:
			printf("Invalid Choice\n");
	}
	scanf("%c", &c);	
	if(c == 'e' || c == 'E')
		break;	
	}
	return 0;
}
