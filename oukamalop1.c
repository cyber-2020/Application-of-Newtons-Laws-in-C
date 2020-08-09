/*
            Electrical and Computer Engineering
            **************************************************************************************************************
            Purpose - to determine whether the blown dart from position (x=0,y=0) with initial velocity 'vo' 
                               hits the banana that has been dropped from ('xo','yo') position.                       
            **************************************************************************************************************
            Data Files
            cp10950.txt - input data file containing vo,xo,yo - dart's initial velocity & position; coordinates of banana
            **************************************************************************************************************
            Given Equations & Values
            x=xi+vox*t+(1/2)*ax*t^2;    for both dart and banana
            y=yi+voy*t+(1/2)*ay*t^2;    for both dart and banana
            
            for banana: vo=0,ax=0,ay=-32.1725 ft/sec^2,xi=xo,yi=yo;
            for dart:   xi=0=yi,ax=0,ay=-32.1725 ft/sec^2;
            **************************************************************************************************************
            Symbolic Constants
            NC - Numeric value "(1/2)" that is part of the given equation
            AX  - initial acceleration of both the dart and banana in the horizontal (x-axis) direction
            AY  - initial acceleration of both the dart and banana in the vertical (y-axis) direction
            ************************************************************************************************************* */

/*Preprocessor Directives*/
#include <stdio.h>
#include <math.h>
#define NC .5
#define AX 0
#define AY -32.1725


/* main function starts here */
/* it will determine whether the dart blown by hunter hits or misses 
   the banana dropped by monkey and outputs the result */

main()

{
/* ************************************************************************************************************* */
    /* variable declarations */
        float vo;       /* input, initial velocity of dart */
        float xo;       /* input, initial position of banana in x-axis */
        float yo;       /* input, initial position of banana in y-axis */
        
        float vox;      /* output, initial velocity of dart along x-axis, vox=vo*cos(angle) */
        float voy;      /* output, initial velocity of dart along y-axis, voy=vo*sin(angle) */
        float angle;    /* output, aimed angle of dart, tan(angle)=yo/xo */
        
        float xd;       /* position of dart in x-axis, 'xd=xi+vox*t+(1/2)*ax*t*t' */
        float yd;       /* position of dart in y-axis, 'yd=yi+voy*t+(1/2)*ay*t*t' */  
        float xb;       /* position of banana in x-axis, 'xb=xi+vox*t+(1/2)*ax*t*t' */
        float yb;       /* position of banana in y-axis, 'yd=yi+voy*t+(1/2)*ay*t*t' */
        
        float t;        /* time, in seconds, starts from 0 till dart misses or hits banana */
        float txdb;     /* time in seconds, determines whether dart hits banana along x-axis */ 
        float tydb;     /* time in seconds, determines whether dart hits banana along y-axis */
        int setCount;   /* output, how many sets of numbers the input file contains */
        FILE *fin, *fout;   /* pointers to input and output files */
    
/* ************************************************************************************************************* */
/*                          Begin by opening files & writing title                                               */
/* ************************************************************************************************************* */

        fin = fopen("cp10950.txt","r");
        fout = fopen("oukamalop1.out","w");
        fprintf(fout,"**************************************************************************************\n");
        fprintf(fout,"Electrical and Computer Engineering\n");
        fprintf(fout,"**************************************************************************************\n\n");

/* ************************************************************************************************************* */
/*         Begin input loop, read input parameters, process then loop back until                                 */
/*         end of data file is reached, output the results in the form of a table                                */
/* ************************************************************************************************************* */
            
            setCount=0;     /* Initialize the data set counter */
            
        while(fscanf(fin, "%f %f %f",&xo,&yo,&vo)>0)    /* begin outer while loop */
        {
        /* Count and output the number of data sets */
            setCount = setCount+1;      
            fprintf(fout,"Data set %d",setCount);
            
        /*      echo check input parameters     */
            fprintf(fout,"\n  Horizontal Distance to Tree = %f ft",xo); 
            fprintf(fout,"\n  Height of Monkey in Tree = %f ft",yo);
            fprintf(fout,"\n  Initial Velocity of Dart = %f ft/sec",vo);
        
        /* Calculating the angle of blown dart and output the result */
            angle = (atan((yo/xo)));        
            fprintf(fout,"\n Angle of aim = %f radians",angle);             
        
        /*      write headings for output table     */
            fprintf(fout,"\n\n Time \t\t Dart X \t Dart Y \t Banana X \t Banana Y   \n");
            fprintf(fout," (sec) \t\t  (ft) \t\t  (ft) \t\t   (ft) \t   (ft)\n");
        
        /* Calculate the position of dart and banana from t=0 till hit or miss */
            vox = vo*cos(angle);        /* velocity of dart in horizontal (x-axis) direction */
            voy = vo*sin(angle);        /* velocity of dart in vertical (y-axis) direction */
            
            t=0;                        /* initialize time to zero every time loop executes */
            xb=xo;                      /* position of banana in feet, initial  horizontal distance to banana*/    
            yb=yo;                      /* position of banana in feet, initial height of banana */
            xd = vox*t;                 /* position of dart in feet, 'xd=xi+vox*t+(1/2)*ax*t*t' is simplified */
            yd = voy*t+NC*AY*t*t;       /* position of dart in feet, 'yd=yi+voy*t+(1/2)*ay*t*t' is simplified */
            
            while(((xd<=xb)&&(yd>=0))&&(yb>=0)) /* Inner while loop - skips the loop if yd<0, yb<0, or xd>xb */
            {   
                xd = vox*t;
                yd = voy*t+NC*AY*t*t;
                xb = xo;
                yb = yo+NC*AY*t*t;
            
            /* output the table values in the order 't  xd  yd  xb  yb' */
                fprintf(fout," %f  %f \t %f \t %f \t %f \n",t,xd,yd,xb,yb);
                
                t=t+.1;     /* inrements time by 0.1 each time loop executes */
            }       /* inner while loop ends */
            
            txdb = xo/(vo*cos(angle));  /* calculates txdb(time) dart hits banana along x-axis */
            tydb = yo/(vo*sin(angle));  /* calculates tydb(time) dart hits banana along y-axis */
                
            /*  By simplifing and solving the given equations for t,  
                (in my case for txdb & tydb), we conclude that:
                if 'txdb == tydb', "HIT", if not "MISS" */
            
            if(txdb==tydb) /* if statement start, prints out the message "HIT or MISS' */
            {
                fprintf(fout,"\n****Dart hit banana between %f and %f\n\n",(t-.2),(t-.1));
            }
            else 
            {
                fprintf(fout,"\n****Missed****\n\n");
            }   
            /* end of if statement */
            
        }   /* end of outer while loop */    

}    /* end of main */        
        
                
/* ************************************************************************************************************* */
/*                                          End of code                                                          */
/* ************************************************************************************************************* */
            
    
