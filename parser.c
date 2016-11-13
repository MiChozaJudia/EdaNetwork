#include "parser.h"

#include <stdio.h>
#define OPTION '-'

int parseCmdLine (int argc, char *argv[], pCallback p, void *userData){
    int i,j,ret=0;
    
    for(i=1;i<argc && ret!=-1 && ret!=-2;i++){
        if(*(argv[i])== OPTION){                            //me fijo si es opcion
	/*Esta parte analiza las opciones*/
            if(*(argv[i]+1)!=NULL)
            {                       //me fijo si hay key
                if(i<(argc-1))      //me fijo si no es el ultimo argv[]
                {
                    if( p(argv[i]+1,argv[i+1],userData) == 0)
                    {
                        ret=CALL_ERROR;     //el callback devolvio error
                    }
                    else
                    {
                        ret++;      //opcion correcta, aumento el contador de opciones y parametros
                        i++;        //aumento el contador de argv ya que las opciones usan 2 espacios
                    }
                }
                else
                {
                    ret=SYNTAX_ERROR;         //no hay value
                }
            }
            else
            {
                ret=SYNTAX_ERROR;             //no hay key
            }
        }else{
	/*Esta parte analiza los parametros*/
            if(p(NULL,argv[i],userData)==0){
                ret=CALL_ERROR;             //el callback devolvio error
            }else{
                ret++;                      //parametro correcto, aumento contador
            }
        }
    }
    return ret;
}