   {
        printf("aaa");
    }
    else
    {
        if(strcmp(order2,"/p")!=0)
        {
            FILE *file1=fopen("src/step1_1/test1.c","r");
            char buf1[1024];
            while(fgets(buf1,sizeof(buf1),file1)!=NULL)
