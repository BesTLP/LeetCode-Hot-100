    #include "vector"
    #include "iostream"
    class Solution 
    {
    public:
        int maxArea(std::vector<int>& height) 
        {
            int lower = 0;
            int upper = height.size() - 1;
            int maxArea = 0;
            while (lower < upper)
            {
                maxArea = std::max((upper -lower) * std::min(height[lower], height[upper]), maxArea);
                if (height[lower] > height[upper])
                {
                    upper--;
                }
                else
                {
                    lower++;
                }
            }
            return maxArea;
        }
    };