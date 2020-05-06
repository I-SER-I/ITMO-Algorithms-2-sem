using System;
using System.Collections.Generic;

namespace Algo
{
    class Search2
    {
        static int[] GetPrefix(string s)
        {
            int[] result = new int[s.Length];
            for (int i = 1; i < s.Length; i++)
            {
                int k = result[i - 1];
                while (k > 0 && s[i] != s[k])
                    k = result[k - 1];
                if (s[i] == s[k])
                    result[i] = k + 1;
                else
                    result[i] = k;
            }
            return result;
        }
        static List<int> KMP(string pat, string text)   
        {   
            List<int> result = new List<int>();
            int[] prefix = GetPrefix(pat + "#" + text);
            for(int i = 0; i < text.Length; i++)
                if (prefix[pat.Length + i + 1] == pat.Length)
                    result.Add(i - pat.Length + 2);
            return result;
        }
        static void Main(string[] args)
        {
            string pat = Console.ReadLine();
            string text = Console.ReadLine();
            List<int> answer = KMP(pat, text);
            Console.WriteLine(answer.Count);
            foreach (int i in answer)
                Console.Write(i + " ");
        }   
    }
}
