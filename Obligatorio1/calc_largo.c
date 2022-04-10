// Devuelve cuantos bits se precisan para representar un UINT dado
// la guardo por las dudas, no la termine usando
int calc_largo(unsigned int valor){
	if(valor == 0){
		return 0;
	}	
	
	int i = sizeof(unsigned int)*CHAR_BIT - 1;
	while(!((valor >> i) & 1)){
		i--;
	}
	
	return (i+1);  
}
