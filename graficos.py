import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

# Datos
bytes = [
10,
100,
1000,
10000,
100000,
1000000]

tiempo_ida_vuelta = [0.001193,
0.001137,
0.001177,
0.001254,
0.002778,
0.112816]

tiempo_ida= [0.000597,
0.000568,
0.000589,
0.000627,
0.001389,
0.056408]

plt.plot(tiempo_ida_vuelta, bytes,'o-', label="Ida y vuelta")
plt.plot(tiempo_ida, bytes,'o-', label="Solo ida")

# Etiquetas de ejes
plt.xlabel("Tiempo en segundos")
plt.ylabel("Tamaño del mensaje (bytes)")

# Título y leyenda
plt.title("Tiempo vs Tamaño del mensaje")
plt.legend()

# Configurar eje Y para mostrar números normales
ax = plt.gca()
ax.yaxis.set_major_formatter(ScalarFormatter())
ax.ticklabel_format(style='plain', axis='y')  # fuerza números planos

# Mostrar gráfico
plt.show()