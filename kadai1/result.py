import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


file_name1 = "result_changeA1.csv"
name_ = ["A", "TS1", "TS2", "EC1", "EC2"]
df = pd.read_csv(file_name1, names=name_, encoding='cp932')
# print(df)

ax = df.plot(x="A", y="TS1", color='blue', label='Thermal stress 1', figsize=(3,2))
df.plot(x="A", y="TS2", color='red', label='Thermal stress 2', ax=ax)
ax.set_xlabel("Area [m^2]")
ax.set_ylabel("Thermal stress [N/m^2]")
plt.show()
fig = ax.get_figure()
fig.subplots_adjust(bottom=0.2)
fig.savefig("TS_A1.png")

ax = df.plot(x="A", y="EC1", color='blue', label='Expand and Contract 1', figsize=(3,2))
df.plot(x="A", y="EC2", color='red', label='Expand and Contract 2', ax=ax)
ax.set_xlabel("Area [m^2]")
ax.set_ylabel("Expand and Contract [m]")
plt.show()
fig = ax.get_figure()
fig.subplots_adjust(bottom=0.2)
fig.savefig("EC_A1.png")





file_name2 = "./result_changeL1.csv"
name_ = ["L", "TS1", "TS2", "EC1", "EC2"]
df = pd.read_csv(file_name2, names=name_, encoding='cp932')
# print(df)

ax = df.plot(x="L", y="TS1", color='blue', label='Thermal stress 1', figsize=(3,2))
df.plot(x="L", y="TS2", color='red', label='Thermal stress 2', ax=ax)
ax.set_xlabel("Length [m]")
ax.set_ylabel("Thermal stress [N/m^2]")
plt.show()
fig = ax.get_figure()
fig.subplots_adjust(bottom=0.2)
fig.savefig("TS_L1.png")

ax = df.plot(x="L", y="EC1", color='blue', label='Expand and Contract 1', figsize=(3,2))
df.plot(x="L", y="EC2", color='red', label='Expand and Contract 2', ax=ax)
ax.set_xlabel("Length [m]")
ax.set_ylabel("Expand and Contract [m]")
plt.show()
fig = ax.get_figure()
fig.subplots_adjust(bottom=0.2)
fig.savefig("EC_L1.png")