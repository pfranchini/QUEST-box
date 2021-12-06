import numpy as np
import matplotlib.pyplot as plt

data1 = np.loadtxt('result')
data2 = np.loadtxt('estar')

ax1 = plt.gca()
ax1.scatter(data1[:,0]/1000,data1[:,1]*100, c='b', label='Geant4')
ax1.set_xscale('log')

ax2 = plt.gca()
ax2.scatter(data2[:,0],data2[:,1]+data2[:,2], c='r', label='ESTAR')
ax2.set_xscale('log')



plt.xlim([0.0005,10])
plt.title("Mass stopping power")
plt.xlabel('Kinetic Energy [MeV]')
plt.ylabel(r'dE/$\rho$dx [MeVg/cm$^2$]')
plt.legend(loc='upper right');

plt.savefig('StoppingPower.png')
plt.savefig('StoppingPower.pdf')

plt.show()


