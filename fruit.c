#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DATABASE "supermarket.db"
#define N 256

void doinsert(sqlite3 *db);
void dodelete(sqlite3 *db);
void doupdate(sqlite3 *db);
void doquery(sqlite3 *db);
void doquery1(sqlite3 *db);

int main(int argc, const char *argv[])
{
	//open database
	sqlite3 *db;
	if (sqlite3_open(DATABASE, &db) != SQLITE_OK)
	{
		printf("%s\n", sqlite3_errmsg(db));
		return -1;
	}
	else
	{
		printf("open database %s successfully!\n", DATABASE);
	}

	//create table
	char *errmsg;
	if (sqlite3_exec(db, "create table if not exists fruit(name char, unitPrice float, quantity float, totalPrice float, purchaseDate char, shippingTime char, customerVisitTime char)", NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return -1;

	}
	else
	{
		printf("create table successfully\n");
	}
	
	//insert delete update query
	int n = 0;
	while (1)
	{
		printf("*****************************************\n");
		printf("1.insert 2.delete 3.update 4.query 5.exit\n");
		printf("*****************************************\n");
		printf("input:");
		scanf("%d", &n);
		switch (n)
		{
			case 1:
				doinsert(db);
				break;
			case 2:
				dodelete(db);
				break;
			case 3:
				doupdate(db);
				break;
			case 4:
				//doquery(db);
				doquery1(db);
				break;
			case 5:
				printf("exiting...\n");
				sqlite3_close(db);
				exit(0);
				break;
			default:
				printf("invalid input\n");
				break;
		}
	}
	return 0;
}

void doinsert(sqlite3 *db)
{
	char sql[N] = {};
	char *errmsg;

	char name[12];
	printf("input name:");
	scanf("%s", name);
	getchar();

	float unitPrice;
	printf("input unitPrice:");
	scanf("%f", &unitPrice);

	float quantity;
	printf("input quantity:");
	scanf("%f", &quantity);

	float totalPrice = unitPrice * quantity;

	char purchaseDate[11];
	printf("input purchaseDate(YY-MM-DD):");
	scanf("%s", purchaseDate);
	getchar();

	char shippingTime[11];
	printf("input shippingTime(YY-MM-DD):");
	scanf("%s", shippingTime);
	getchar();

	char customerVisitTime[11];
	printf("input customerVisitTime(YY-MM-DD):");
	scanf("%s", customerVisitTime);
	getchar();

	sprintf(sql, "insert into fruit values('%s', %f, %f, %f, '%s', '%s', '%s');", name, unitPrice, quantity, totalPrice, purchaseDate, shippingTime, customerVisitTime);
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return;
	}
	else
	{
		printf("insert successfully!\n");
	}
}

void dodelete(sqlite3 *db)
{
	char sql[N] = {};
	char *errmsg;

	char name[12];
	printf("input name:");
	scanf("%s", name);
	getchar();

	sprintf(sql, "delete from fruit where name='%s';", name);
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return;
	}
	else
	{
		printf("delete successfully!\n");
	}
}

void doupdate(sqlite3 *db)
{
	char sql[N] = {};
	char *errmsg;

	char name[12];
	printf("input name:");
	scanf("%s", name);
	getchar();

	float unitPrice;
	printf("input unitPrice:");
	scanf("%f", &unitPrice);

	float quantity;
	printf("input quantity:");
	scanf("%f", &quantity);

	float totalPrice = unitPrice * quantity;

	char purchaseDate[11];
	printf("input purchaseDate(YY-MM-DD):");
	scanf("%s", purchaseDate);
	getchar();

	char shippingTime[11];
	printf("input shippingTime(YY-MM-DD):");
	scanf("%s", shippingTime);
	getchar();

	char customerVisitTime[11];
	printf("input customerVisitTime(YY-MM-DD):");
	scanf("%s", customerVisitTime);
	getchar();

	sprintf(sql, "update fruit set unitPrice=%f, quantity=%f, totalPrice=%f, purchaseDate='%s', shippingTime='%s', customerVisitTime='%s' where name='%s'", unitPrice, quantity, totalPrice, purchaseDate, shippingTime, customerVisitTime, name);
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return;
	}
	else
	{
		printf("update successfully!\n");
	}
}

int callback(void *arg, int f_num, char **f_value, char **f_name)
{
	int i;
	for (i = 0; i < f_num; i++)
	{
		printf("%s|", f_name[i]);
	}
	puts("");
	for (i = 0; i < f_num; i++)
	{
		printf("%s|", f_value[i]);
	}
	puts("");
	puts("");
	return 0;
}

void doquery(sqlite3 *db)
{
	char sql[N] = "select * from fruit;";
	char *errmsg;
	if (sqlite3_exec(db, sql, callback, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s", errmsg);
	}
	else
	{
		printf("query successfully!\n");
	}
}

void doquery1(sqlite3 *db)
{
	char sql[N] = "select * from fruit;";
	char **resultp;
	int nrow, ncolumn;
	char *errmsg;
	if (sqlite3_get_table(db, sql, &resultp, &nrow, &ncolumn, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else
	{
		printf("query successfully!\n");
	}

	int i = 0, j = 0;
	int index = ncolumn;
	for (j = 0; j < ncolumn; j++)
	{
		printf("%s|", resultp[j]);
	}
	puts("");
	for (i = 0; i < nrow; i++)
	{
		for (j = 0; j < ncolumn; j++)
		{
			printf("%s|", resultp[index++]);
		}
		puts("");
	}
	puts("");
}
