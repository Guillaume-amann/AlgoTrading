import matplotlib.pyplot as plt

categories = ['WAAC','TGR', 'comps', 'Analysts\' Estimate', '52-Week Trading']
starts = [186,197,155,160,109]
values = [251,231,253,222,201]
length = [values[i] - starts[i] for i in range(len(values))]
means = [(start + value) / 2 for start, value in zip(starts[:-1], values[:-1])]

target_price = round(sum(means) / len(means),2)
current_price = 200.40
plt.figure(figsize=(10,6))
plt.barh(categories, length, height=0.5, left=starts, color='royalblue', alpha=1)
plt.axvline(x=current_price, color='black', linestyle=':', label='Current Price')
plt.axvline(x=target_price, color='black', linestyle='-', label='Target Price')
plt.xlim(100, 260)

plt.text(current_price - 8, 1, f'Current Price:\n${current_price}', va='center', ha='right', fontsize=14)
plt.text(target_price + 6, 4, f'Target Price:\n${target_price}', va='center', ha='left', fontsize=14)

plt.show()