class Solution:
    def getMoneyAmount(self, n: int) -> int:
        # dp表示在范围[i,j]内的猜中数字所需要的最小钱
        dp = [[0] * (n+1) for _ in range(n+1)]
        # n-1开始是因为只有最后一个时候是0 已经初始化过了不需要计算
        for i in range(n-1, 0, -1): #不需要计算为0的情况 因为初始化的时候就是全部为0
            for j in range(i+1, n+1): # dp[i][i] = 0
                # 官方题解因为需要先加上选自己以及之前[i, j-1]的最小花费 也可以设置为一个float('inf') 后面都会找到最小值的
                # 这里设置一个dp[i][j]来确定最小值 可以和之前的664题 做对比更清晰思路
                dp[i][j] = j + dp[i][j - 1]
                # 找最小情况 k表是在 [i, j]的范围内 分别猜[i, j-1]的情况
                # j从i+1开始时因为dp[i][i] = 0不需要计算 但是在[i,j]范围内找最小值还是需要从第一个开始找
                # 当然可以在初始化可以优化d[i][j+1] = i 因为加个最少肯定选小的那个
                for k in range(i,j): # i<j 是必然的，因为前面 j=i+1
                    # k!=j 是因为最后一个猜中了 不需要钱 所以k肯定不能最后一个 或者说 这样肯定不是最小值
                    # max规律 j 下面几个数就循环多少次 假设求dp[1][n]
                    # [1,0], [2,5]
                    # [1,1], [3,5]
                    # [1,2], [4,5]
                    # [1,3], [5,5]
                    dp[i][j] = min(dp[i][j], k + max(dp[i][k - 1], dp[k + 1][j]))
        return dp[1][n]