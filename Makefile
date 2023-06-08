all:
	g++ -O3 \
	-I include/eigen-3.4.0 \
	include/calculoAutovectores/calculoAutovectores.cpp \
	analisis/generacionDatos/expPotencia.cpp \
	analisis/generacionDatos/expAutovectores.cpp \
	main.cpp -o main && ./main