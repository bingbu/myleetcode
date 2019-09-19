/*
 * https://leetcode.com/problems/squares-of-a-sorted-array/
 */

class Solution(object):
    def sortedSquares(self, A):
        """
        :type A: List[int]
        :rtype: List[int]
        """
        size = len(A)
        j = 0
        while j <size and A[j] < 0:
            j += 1
        i = j-1
        res = []
        while i >= 0 and j < size:
            if A[i]**2 < A[j]**2:
                res.append(A[i]**2)
                i -= 1
            else:
                res.append(A[j]**2)
                j += 1

        while i>= 0:
            res.append(A[i]**2)
            i -= 1
            
        while j < size:
            res.append(A[j]**2)
            j += 1
                
        return res


if __name__ == "__main__":
    a = [-4, -1, 0, 3, 10]
    b = [-7, -3, 2, 3, 11]
    S = Solution()
    print(S.sortedSquares(a))
    print(S.sortedSquares(b))
