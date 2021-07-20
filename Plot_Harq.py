from matplotlib import pyplot as plt
import numpy as np
import matplotlib as mpl
mpl.rcParams['font.sans-serif'] = ['SimHei']  # 中文字体支持

#export DISPLAY=:0.0

fig, (ax, ax1) = plt.subplots(2, 1)
ax.set_title('HARQ和固定4次传输的比较，TTInum=5000')

#harq
# data1 = [744, 2210, 1182, 284, 38]    #2T1R
# data2 = [808, 2565, 1211, 102, 5]     #2T2R，SB=0
# data3 = [1161, 3209, 784, 17, 0]      #2T2R，SB=1
data1 = [4420, 38, 4.330554]  # 2T1R
data2 = [4686, 5, 5.169830]  # 2T2R，SB=0
data3 = [5171, 0, 5.726104]  # 2T2R，SB=1

#固定重传
data4 = [2469, 31, 2.433992]  # 2T1R
data5 = [2499, 1, 2.769426]  # 2T2R，SB=0
data6 = [2500, 0, 2.775389]  # 2T2R，SB=1

#上传
data7 = [2478, 22, 2.435619]  # 固定4次
data8 = [4257, 42, 4.163106]  # HARQ

size = 3
x = np.arange(size)

# bar = ax.bar(x, data1, tick_label=[
#     '初传成功', '1次重传', '2次重传'])

total_width, n = 0.8, 4
width = total_width / n
x = x - (total_width - width) / 2



bar1 = ax.bar(x, [38,5,0], width=width, label='HARQ错误传输TB数')
bar2 = ax.bar(x + width, [4420,4686,5171],  width=width, tick_label=[
    'SendrN=2;RecvrM=1;', 'SendrN=2;RecvrM=2;SoftCombine_ON=0', 'SendrN=2;RecvrM=2;SoftCombine_ON=1'], label='HARQ成功传输TB数')
bar3 = ax.bar(x + 2 * width, [31,1,0], width=width,
              label='固定4次传输错误TB数')
bar4 = ax.bar(x + 3 * width, [2469, 2499, 2500], width=width,
              label='固定4次传输成功TB数')

for b in bar1:
    height = b.get_height()
    ax.annotate('{}'.format(height),
                xy=(b.get_x() + b.get_width() / 2, height),
                xytext=(0, 3),  # 3 points vertical offset
                textcoords="offset points", color='black',
                ha='center', va='bottom')

for b in bar2:
    height = b.get_height()
    ax.annotate('{}'.format(height),
                xy=(b.get_x() + b.get_width() / 2, height),
                xytext=(0, 3),  # 3 points vertical offset
                textcoords="offset points", color='black',
                ha='center', va='bottom')

for b in bar3:
    height = b.get_height()
    ax.annotate('{}'.format(height),
                xy=(b.get_x() + b.get_width() / 2, height),
                xytext=(0, 3),  # 3 points vertical offset
                textcoords="offset points", color='black',
                ha='center', va='bottom')

for b in bar4:
    height = b.get_height()
    ax.annotate('{}'.format(height),
                xy=(b.get_x() + b.get_width() / 2, height),
                xytext=(0, 3),  # 3 points vertical offset
                textcoords="offset points", color='black',
                ha='center', va='bottom')
ax.set_ylim([0, 5600])
ax.legend()


total_width, n = 0.8, 2
width = total_width / n
x = x - (total_width - width) / 2

bar1 = ax1.bar(x, [4.330554, 5.169830, 5.726104],
               width=width, label='HARQ的平均传输速率(mbps)')
bar2 = ax1.bar(x + width, [2.433992, 2.769426, 2.775389],  width=width, tick_label=[
    'SendrN=2;RecvrM=1;', 'SendrN=2;RecvrM=2;SoftCombine_ON=0', 'SendrN=2;RecvrM=2;SoftCombine_ON=1'], label='固定4次传输的平均传输速率(mbps)')


for b in bar1:
    height = b.get_height()
    ax1.annotate('{}'.format(height),
                xy=(b.get_x() + b.get_width() / 2, height),
                xytext=(0, 3),  # 3 points vertical offset
                textcoords="offset points", color='black',
                ha='center', va='bottom')

for b in bar2:
    height = b.get_height()
    ax1.annotate('{}'.format(height),
                xy=(b.get_x() + b.get_width() / 2, height),
                xytext=(0, 3),  # 3 points vertical offset
                textcoords="offset points", color='black',
                ha='center', va='bottom')
ax1.legend()
ax1.set_ylim([0, 6.5])

plt.show()
