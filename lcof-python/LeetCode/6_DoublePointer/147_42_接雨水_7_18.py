from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        # 按行求 单调栈->存储下标
        stack = [0]
        area = 0
        for i in range(1,len(height)):
            if height[i] < height[stack[-1]]:
                stack.append(i)
            elif height[i] == height[stack[-1]]:# 解决相等情况 这里弹出再加入 可以再计算面积时 少减一次 跟结果没有关系
                stack.pop()
                stack.append(i)
            else:
                # 持续判断 计算面积 stack[-1] 给的是索引
                while stack and height[i] > height[stack[-1]]:
                    mid = stack.pop()
                    # 检查是否为空 [] is not None 是固定为True的
                    if stack:
                        h = min(height[i], height[stack[-1]]) - height[mid]
                        weight = i-stack[-1]-1
                        area += weight * h
                stack.append(i)
        return area
class Solution:
    def trap(self, height: List[int]) -> int:
        if not height:
            return 0
        # 按列求
        left, right = 0, len(height) - 1
        # 两边最大值
        left_max, right_max = 0, 0
        total_water = 0
        # 哪边小 哪边开始装水
        while left < right:
            # 求每一列能装多少水
            if height[left] < height[right]:
                # 最高点不能装水
                if height[left] >= left_max:
                    left_max = height[left]
                else:
                    total_water += left_max - height[left] # 因为右边有更高的 所以可以蓄水 所以只需要计算左边最大值-自己高度 就是蓄水量了
                left += 1
            else:
                if height[right] >= right_max:
                    right_max = height[right]
                else:
                    total_water += right_max - height[right]
                right -= 1
        
        return total_water