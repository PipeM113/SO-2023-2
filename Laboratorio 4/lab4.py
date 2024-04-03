# importar Thread, Lock, time
from threading import Thread, Lock, Condition, Timer
import datetime
import time
import random

cantidad_personas = 500  # cantidad de personas que se crean


class Departamento:
    def __init__(self, nombre, capacidad_fila, consulta, capacidad_depto, archivo):
        self.nombre = nombre  # nombre del departamento
        self.consulta = consulta  # duración de la consulta
        self.capacidad_fila = capacidad_fila  # capacidad de la fila
        self.capacidad_depto = capacidad_depto  # capacidad del departamento
        self.fila = []  # fila de espera
        self.departamento = []  # lista de personas en el departamento
        self.libre = True  # True si no está haciendo consultas
        self.filaLllena = False  # True si la fila está llena
        self.lockEntrada = Lock()  # lock para la entrada
        self.lockDepto = Lock()  # lock para el departamento
        self.lockFila = Lock()  # lock para la fila
        # condition para la entrada
        self.condEntrada = Condition(self.lockEntrada)
        # condition para el departamento
        self.condDepto = Condition(self.lockDepto)
        self.condFila = Condition(self.lockFila)  # condition para la fila
        # condition para el archivo
        self.archivo = archivo  # archivo en el que se imprime
        self.tiempo_limite = 2 * consulta  # tiempo limite para la consulta
        self.timer = None  # timer para el tiempo limite
        self.tiempo_consulta = time.time()  # tiempo de inicio de la consulta

    def reiniciar_timer(self):
        self.timer = Timer(self.tiempo_limite, self.realizar_consulta)
        self.timer.start()

    def realizar_consulta(self):
        with self.condDepto:
            if self.timer != None and self.timer.is_alive():
                self.timer.cancel()
            if len(self.fila) != 0:
                self.reiniciar_timer()
            self.libre = False
            while (len(self.fila) > 0 and len(self.departamento) < self.capacidad_depto):
                self.departamento.append(self.fila.pop())
            if len(self.fila) < self.capacidad_fila:
                self.filaLllena = False
                with self.condFila:
                    self.condFila.notify_all()
            hora = datetime.datetime.now()
            hora = hora.strftime("%H:%M:%S.%f%z")
            for persona in self.departamento:
                persona.consulta += hora + ", "
                persona.consultas += 1
                persona.consulta += str(persona.consultas)
                self.archivo.write(persona.consulta + "\n")
                self.archivo.flush()
            time.sleep(self.consulta)
            while len(self.departamento) > 0:
                p = self.departamento.pop()
                with p.cond:
                    p.consulto = True
                    p.cond.notify_all()
            self.libre = True
            self.condDepto.notify_all()


class Persona:
    def __init__(self, id):
        self.id = id  # id de la persona
        self.consultas = 0  # cantidad de consultas que ha hecho
        self.depto = 0  # departamento al que quiere consultar
        self.ant = -1  # departamento anterior que consultó
        self.consulta = ""  # string para imprimir
        self.patio = "Persona" + \
            str(self.id)+", "  # string para imprimir
        self.lock = Lock()  # lock para la persona
        self.cond = Condition(self.lock)  # condition para la persona
        self.consulto = False  # True si ya consultó

    def ingresar(self, patio):
        if self.consultas == 0:
            # añadirle al patio la hora de entrada
            hora = datetime.datetime.now()
            hora = hora.strftime("%H:%M:%S.%f%z")
            self.patio += hora + ", "
            patio.personas += 1
            patio.filas[self.depto].append(self)
        elif self.consultas == 1:
            patio.filas[self.depto].append(self)
        else:
            patio.archivo.write(self.patio + "\n")
            patio.archivo.flush()

    def pasar_fila(self, patio, departamentos):
        with departamentos[self.depto].condFila:
            while not (patio.filas[self.depto].index(self) == 0 and departamentos[self.depto].filaLllena == False):
                departamentos[self.depto].condFila.wait()
            patio.filas[self.depto].pop(0)
            departamentos[self.depto].fila.append(self)
            hora = datetime.datetime.now()
            hora = hora.strftime("%H:%M:%S.%f%z")
            self.consulta += hora + ", "
            self.patio += ", "+departamentos[self.depto].nombre + ", " + hora
            if (len(departamentos[self.depto].fila) == departamentos[self.depto].capacidad_fila):
                departamentos[self.depto].filaLllena = True
            if departamentos[self.depto].timer != None and departamentos[self.depto].timer.is_alive():
                departamentos[self.depto].timer.cancel()
            departamentos[self.depto].reiniciar_timer()
            departamentos[self.depto].condFila.notify_all()

    def revisar_consulta(self, departamentos):
        if (departamentos[self.depto].libre and len(departamentos[self.depto].fila) >= departamentos[self.depto].capacidad_depto):
            departamentos[self.depto].realizar_consulta()

    def proceso(self, patio, departamentos):
        while self.consultas < 2:
            self.depto = random.randint(0, 6)
            while self.depto == self.ant:
                self.depto = random.randint(0, 6)
            self.ant = self.depto
            self.consulta = "Persona" + \
                str(self.id) + ", "
            self.ingresar(patio)
            self.pasar_fila(patio, departamentos)
            self.revisar_consulta(departamentos)
            with self.cond:
                while self.consulto == False:
                    self.cond.wait()
            self.consulto = False
        self.ingresar(patio)


class Patio:
    def __init__(self):
        # 0 = Matematicas, 1 = Informatica, 2 = Fisica, 3 = Quimica, 4 = DEFIDER, 5 = Mecanica, 6 = Minas
        self.filas = [[] for i in range(7)]  # filas de espera
        # cantidad de personas que han ingresado al patio (solo se cuenta la primera vez)
        self.personas = 0
        # archivo en el que se imprime
        self.archivo = open("PdLamparas.txt", "w")


archMate = open("Departamento_de_Matematicas.txt", "w")
archInfo = open("Departamento_de_Informatica.txt", "w")
archFis = open("Departamento_de_Fisica.txt", "w")
archQui = open("Departamento_de_Quimica.txt", "w")
archDefider = open("DEFIDER.txt", "w")
archMech = open("Departamento_de_Mecanica.txt", "w")
archMin = open("Departamento_de_Minas.txt", "w")

Mat = Departamento("Matematicas", 20, 9, 10, archMate)
Inf = Departamento("Informatica", 8, 5, 2, archInfo)
Fis = Departamento("Fisica", 15, 7, 5, archFis)
Qui = Departamento("Quimica", 6, 4, 3, archQui)
Defider = Departamento("DEFIDER", 6, 1, 5, archDefider)
Mec = Departamento("Mecanica", 9, 4, 4, archMech)
Min = Departamento("Minas", 7, 5, 2, archMin)

departamentos = [Mat, Inf, Fis, Qui, Defider, Mec, Min]
patio = Patio()

if __name__ == "__main__":
    personas = 0
    threads = []
    for i in range(cantidad_personas):
        p = Persona(i+1)
        thread = Thread(target=p.proceso, args=(patio, departamentos))
        threads.append(thread)
        thread.start()
    for thread in threads:
        thread.join()
    for i in range(7):
        departamentos[i].archivo.close()
    patio.archivo.close()
