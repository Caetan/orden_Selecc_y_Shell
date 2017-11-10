#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>

void ord_sel (int v [], int n){
	int i = 0;
	int j = 0;
	int minj = 0;
	int minx = 0;
	for(i=0; i<(n-1); i++){  
		minj = i;
		minx = v[i];
		for(j=i+1; j<n; j++){
			if(v[j] < minx){
				minj = j;
				minx = v[j];
			}
		}
		v[minj] = v[i];
		v[i] = minx; 
	}
}

void ord_shell (int v [], int n){
	int incremento = n;
	int i = 0;
	int tmp = 0;
	int j = 0;
	bool seguir = true;
	do{
		incremento = incremento/2;
		for (i=incremento; i<n; i++){
			tmp = v[i];
			j = i;
			seguir = true;
			while(((j-incremento) >= 0) && seguir){
				if(tmp<=v[j-incremento]){
					v[j] = v[j-incremento];
					j = j-incremento;
				} else {
					seguir = false;
				}
			}
			v[j] = tmp;
		}
	}while(incremento>1);
}

void ascendente (int v[], int n){
	int i;
	for (i=0; i < n; i++)
		v[i] = i;
}

void descendente (int v[], int n){
	int i;
	for (i=0; i < n; i++)
		v[i] = n-i;
}

void inicializar_semilla () {
	srand(time(NULL));
}

void aleatorio (int v[], int n){ 
	int i, m=2*n+1;
	for (i=0; i < n; i++){
		v[i] = (rand() % m) - n;
	}
}

double microsegundos (){
	struct timeval t;
	if(gettimeofday(&t, NULL) <0 ){
		return 0.0;
	}
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
	
void test_sel (void(* inicializacion)(int [],int), int t, int p){
	int i = 0;
	int cont = 0;
	int v[t];
	inicializacion (v, t);
	if(p == 0){
		printf("Ordenacion por seleccion con inicializ");
		printf("acion aleatoria\n");
	} else {
		printf("Ordenacion por seleccion con inicializa");
		printf("cion descendente\n");
	}
	printf("[ ");
	for(i=0; i<t; i++){ 
		printf("%i ", v[i]);
		if((i < (t-1)) && (v[i] <= v[i+1]))
			cont++;
	}
	printf("]\n");
	if(cont == (t-1)){
		printf("¿ordenado?: 1\n");
	} else {
		printf("¿ordenado?: 0\n");
		printf("ordenando...\n");
		ord_sel (v, t);
		cont = 0;
		printf("[ ");
		for(i=0; i<t; i++){
			printf("%i ", v[i]);
			if(i<t-1 && (v[i] <= v[i+1]))
				cont++;
		}
		printf("]\n");
		if(cont == (t-1))
			printf("¿ordenado?: 1\n\n");
		else
			printf("¿ordenado?: 0\n\n");
	}
}

void test_shell (void(* inicializacion)(int [],int), int t, int p){
	int i = 0;
	int cont = 0;
	int v[t];
	inicializacion (v, t);
	if(p == 0){
		printf("Ordenacion por Shell con inicializ");
		printf("acion aleatoria\n");
	} else {
		printf("Ordenacion por Shell con inicializa");
		printf("cion descendente\n");
	}
	printf("[ ");
	for(i=0; i<t; i++){ 
		printf("%i ", v[i]);
		if((i < (t-1)) && (v[i] <= v[i+1]))
			cont++;
	}
	printf("]\n");
	if(cont == (t-1)){
		printf("¿ordenado?: 1\n");
	} else {
		printf("¿ordenado?: 0\n");
		printf("ordenando...\n");
		ord_sel (v, t);
		cont = 0;
		printf("[ ");
		for(i=0; i<t; i++){
			printf("%i ", v[i]);
			if(i<t-1 && (v[i] <= v[i+1]))
				cont++;
		}
		printf("]\n");
		if(cont == (t-1))
			printf("¿ordenado?: 1\n\n");
		else
			printf("¿ordenado?: 0\n\n");
	}
}

void pintarTablaSel (int cont_a, int n, double t_a){

	if(cont_a == 1){
		printf("(*)");
		printf("%12i%18f%20f%20f%20f\n", n, t_a, t_a/(pow (n,1.8)), 
		t_a/(pow (n,2)), t_a/(pow (n,2.2)));
	}else{
		printf("%15i%18f%20f%20f%20f\n", n, t_a, t_a/(pow (n,1.8)), 
		t_a/(pow (n,2)), t_a/(pow (n,2.2)));	
	}	
	
}

void pintarTablaShell_Asc (int cont_b, int n, double t_b){
        
	if(cont_b == 1){
		printf("(*)");
		printf("%12i%18f%20f%20f%20f\n", n, t_b, t_b/n, 
		t_b/(pow (n, 1.15)), t_b/(pow (n,1.3)));
	}else{
		printf("%15i%18f%20f%20f%20f\n", n, t_b, t_b/n, 
		t_b/(pow (n, 1.15)), t_b/(pow (n,1.3)));	
	}
}

void pintarTablaShell_Desc (int cont_b, int n, double t_b){
        
	if(cont_b == 1){
		printf("(*)");
		printf("%12i%18f%20f%20f%20f\n", n, t_b, t_b/n, 
		t_b/(pow (n, 1.15)), t_b/(pow (n,1.3)));
	}else{
		printf("%15i%18f%20f%20f%20f\n", n, t_b, t_b/n, 
		t_b/(pow (n, 1.15)), t_b/(pow (n,1.3)));	
	}
}

void pintarTablaShell_Alea (int cont_b, int n, double t_b){
        
	if(cont_b == 1){
		printf("(*)");
		printf("%12i%18f%20f%20f%20f\n", n, t_b, t_b/(n*log(n)), 
		t_b/(pow (n, 1.2)), t_b/(pow (n,1.3)));
	}else{
		printf("%15i%18f%20f%20f%20f\n", n, t_b, t_b/(n*log(n)), 
		t_b/(pow (n, 1.2)), t_b/(pow (n,1.3)));	
	}
}

void t_ejecucionSel (int n, void(* inicializacion)(int [],int)){
	int v[n];
	int j = 0;
	int cont_a = 0;
	double t_ini_a, t_fin_a, t_a, t_a2, t_a_aux;

	inicializacion (v,n);
	t_ini_a = microsegundos ();
	ord_sel (v,n);
	t_fin_a = microsegundos ();
	t_a = t_fin_a - t_ini_a;

	if(t_a < 500){
		cont_a = 1;
		t_ini_a = microsegundos();
		for(j=0; j<10000; j++){
			inicializacion (v,n);
			ord_sel (v,n);
		}
		t_fin_a = microsegundos ();
		t_a_aux = t_fin_a - t_ini_a;
		t_ini_a = microsegundos();
		for(j=0; j<10000; j++){
			inicializacion (v,n);
		}
		t_fin_a = microsegundos ();
		t_a2 = t_fin_a - t_ini_a;
		t_a = (t_a_aux - t_a2) / 10000;
	}
	pintarTablaSel (cont_a, n, t_a);
}


void t_ejecucionShell (int n, void(* inicializacion)(int [],int), int modo){
	int *v;
	int j = 0;
	int cont_b = 0;
	double t_ini_a, t_fin_a, t_a, t_a2, t_a_aux;
	v = (int *)malloc(n*sizeof(int));

	inicializacion (v,n);
	t_ini_a = microsegundos ();
	ord_shell (v,n);
	t_fin_a = microsegundos ();
	t_a = t_fin_a - t_ini_a;

	if(t_a < 500){
		cont_b = 1;
		t_ini_a = microsegundos ();
		for(j=0; j<10000; j++){
			inicializacion (v,n);
			ord_shell (v,n);
		}
		t_fin_a = microsegundos ();
		t_a_aux = t_fin_a - t_ini_a;
		t_ini_a = microsegundos ();
		for(j=0; j<10000; j++){
			inicializacion (v,n);
		}
		t_fin_a = microsegundos ();
		t_a2 = t_fin_a - t_ini_a;
		t_a = (t_a_aux - t_a2) / 10000;
	}

	if(modo == 1)
		pintarTablaShell_Asc (cont_b, n, t_a);
	if(modo == 2)
		pintarTablaShell_Desc (cont_b, n, t_a);
	if(modo == 3)
		pintarTablaShell_Alea (cont_b, n, t_a);
				
	free(v);
}

void ejec(int n, int alg, void(* inicializacion)(int [],int), int modo){
	if(alg == 1)
		t_ejecucionSel (n, inicializacion);
	if(alg == 2)
		t_ejecucionShell (n, inicializacion, modo);
}

void funcion_submain (){
	int i = 0;
	printf("\n%s", "Ordenacion por seleccion con inicializacion");
	printf(" ascendente\n");
	printf("%15s%18s%20s%20s%20s\n", "n", "t(n)", "t(n)/n^1.8", 
	"t(n)/n^2", "t(n)/n^2.2");
	for(i=500; i <= 64000; i=i*2)
		ejec (i, 1, ascendente, 0);
	
	printf("\n\n%s", "Ordenacion por Shell con inicializacion");
	printf(" ascendente\n");
	printf("%15s%18s%20s%20s%20s\n", "n", "t(n)", "t(n)/n", 
	"t(n)/n^1.15", "t(n)/n^1.3");
	for(i=500; i <= 64000; i=i*2)
		ejec (i, 2, ascendente, 1);
		
	printf("\n\n%s", "Ordenacion por seleccion con inicializacion");
	printf(" descendente\n");
	printf("%15s%18s%20s%20s%20s\n", "n", "t(n)", "t(n)/n^1.8", 
	"t(n)/n^2", "t(n)/n^2.2");
	for(i=500; i <= 64000; i=i*2)
		ejec (i, 1, descendente, 0);
}

void funcion_submain2 (){
	int i = 0;
	printf("\n\n%s", "Ordenacion por Shell con inicializacion");
	printf(" descendente\n");
	printf("%15s%18s%20s%20s%20s\n", "n", "t(n)", "t(n)/n", 
	"t(n)/n^1.15", "t(n)/n^1.3");
	for(i=500; i <= 64000; i=i*2)
		ejec (i, 2, descendente, 2);
		
	printf("\n\n%s", "Ordenacion por seleccion con inicializacion");
	printf(" desordenado\n");
	printf("%15s%18s%20s%20s%20s\n", "n", "t(n)", "t(n)/n^1.8", 
	"t(n)/n^2", "t(n)/n^2.2");
	for(i=500; i <= 64000; i=i*2)
		ejec (i, 1, aleatorio, 0);

	printf("\n\n%s", "Ordenacion por Shell con inicializacion");
	printf(" desordenado\n");
	printf("%15s%18s%20s%20s%20s\n", "n", "t(n)", "t(n)/(n*log(n))", 
	"t(n)/n^1.2", "t(n)/n^1.3");
	for(i=500; i <= 64000; i=i*2)
		ejec (i, 2, aleatorio, 3);
}

int main(){
	inicializar_semilla ();
	test_sel (aleatorio, 17, 0);
	test_sel (descendente, 10, 1);
	test_shell (aleatorio, 17, 0);
	test_shell (descendente, 10, 1);
	funcion_submain ();
	funcion_submain2 ();
	
	return 0;
}
