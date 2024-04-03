# Definir las variables
PYTHON = python3
SOURCE = lab4.py

# Definir las reglas
all: run

run:
	$(PYTHON) $(SOURCE)

clean:
	rm -rf __pycache__
	rm -f *.pyc *.pyo
	find . -type f -name '*.txt' -and -not -name 'README.txt' -delete
	
	
	
