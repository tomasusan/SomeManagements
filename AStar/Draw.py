import matplotlib.pyplot as plt
import numpy as np

# ===============================
# 读取迷宫矩阵
# ===============================
maze_file = "..\\AStar\\CacheFile.txt"
maze_lines = [line.strip() for line in open(maze_file, encoding="utf-8") if line.strip()]

rows = len(maze_lines)
cols = len(maze_lines[0])

maze = np.zeros((rows, cols), dtype=int)
start_points = []
end_points = []

for i, line in enumerate(maze_lines):
    for j, ch in enumerate(line):
        if ch == '#':
            maze[i, j] = 1  # 墙
        elif ch in ('*', 'O', 'S', 'E'):
            maze[i, j] = 0  # 通路
        if ch == 'S':
            start_points.append((i, j))
        elif ch == 'E':
            end_points.append((i, j))

# ===============================
# 读取路径文件
# ===============================
path_file = "..\\AStar\\Path.txt"
paths = []
with open(path_file, encoding="utf-8") as f:
    for line in f:
        nums = list(map(int, line.split()))
        path = [(nums[i], nums[i+1]) for i in range(0, len(nums), 2)]
        if path:
            paths.append(path)

# ===============================
# 绘制迷宫与路径
# ===============================
plt.figure(figsize=(10, 10))
plt.imshow(maze, cmap='gray_r')  # 黑墙白路

colors = ['red', 'blue', 'green', 'orange', 'purple', 'cyan', 'magenta']

# 绘制每一条路径
for idx, path in reversed(list(enumerate(paths))):
    y, x = zip(*path)
    plt.plot(x, y, color=colors[idx % len(colors)], linewidth=3, label=f'Path {idx+1}')
    plt.scatter(x[0], y[0], color='lime', s=80, edgecolors='black', zorder=5)


# 绘制所有起点(S)与终点(E)
for (y, x) in start_points:
    plt.scatter(x, y, color='lime', s=100, edgecolors='black', zorder=6, label='S' if 'S' not in plt.gca().get_legend_handles_labels()[1] else "")
for (y, x) in end_points:
    plt.scatter(x, y, color='red', s=100, edgecolors='black', zorder=6, label='E' if 'E' not in plt.gca().get_legend_handles_labels()[1] else "")

plt.legend(loc='upper right', fontsize=8)
plt.axis('off')

save_path = "..\\AStar\\MazeWithPaths.png"
plt.savefig(save_path, bbox_inches='tight', pad_inches=0, dpi=100)
plt.close();

print(f"✅ Maze draw finished, saved to：{save_path}")
