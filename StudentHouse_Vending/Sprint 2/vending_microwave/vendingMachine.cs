using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace vending_microwave
{
    public class VendingMachine
    {
        private List<Product> list = new List<Product> {
            new Product("Water", 12), 
            new Product("Snacks", 6),
            new Product("Napkins", 12),
            new Product("Waffle", 15),
            new Product("Chocolate", 10),
            new Product("Juice", 15),
            new Product("Coca Cola", 10),
            new Product("Sticks", 15),
            new Product("Tennis balls", 10),
            new Product("Condoms", 10),
            new Product("Croissant", 8)
            };
        
        public void addProduct(Product t)
        {
            list.Add(new Product(t.getName(), t.getCount()));
        }

        public void addCount(String name, int count)
        {
            for(int i = 0; i < list.Count; i++)
            {
               if(list[i].getName() == name)
                {
                    list[i].addCount(count);
                }
            }
        }

        public bool getProduct(int num)
        {
            for(int i = 0; i < list.Count; i++)
            {
                if (list[i].getNumber() == num)
                {
                    if (list[i].getCount() > 1)
                    {
                        list[i].removeOne();
                    }
                    else
                    {
                        //list.RemoveAt(list.FindIndex(a => a.getName().Contains(list[i].getName())));
                        if (list[i].getCount() == 1)
                        {
                            list[i].removeOne();
                        }
                        return false;
                    }
                    return true;
                }
            }
            return false;
        }

        public List<Product> getList()
        {
            return list;
        }
    }
}
