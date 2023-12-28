            {
                printf("%d  %s",num,buf1);
                num++;
            }
        }
        else
        {
            num=1;
            FILE *file2=fopen("src/step1_1/test1.c","r");
            char buf2[1024];
            while(fgets(buf2,sizeof(buf2),file2)!=NULL)
            {
                printf("%d  %s",num,buf2);
                num++;
                if(num==11)
                {
                    while(getchar()!='q');
                    num=1;
                }
            }
        }
    }
    /**********   End   **********/
    return 0; 
}
