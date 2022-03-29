using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vending_microwave
{
    public class Product
    {
     private readonly String name;
     private int count;
     public static int num = 0;
     private int number;

        public Product(String name, int c) { this.name = name; this.count = c; num++; number = num; }

        public String getName()
        {
            return name;
        }

        public int getCount()
        {
            return count;
        }

        public int getNumber()
        {
            return number;
        }

        public void addCount(int val)
        {
            count += val;
        }

        public void removeOne()
        {
            count--;
        }

        public void fixNumber()
        {
            number--;
        }
    }
}
