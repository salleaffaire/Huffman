#ifndef HUFFMAN_HPP_
#define HUFFMAN_HPP_

#include <list>
#include <iostream>

// **************************************************************

// **************************************************************

template <class T>
class CSymbol {
public:
   CSymbol(T symbol) : mSymbol(symbol), mCode(0), mLenght(0) {}

   T            mSymbol;
   unsigned int mCode;
   unsigned int mLenght;

   void OutputCode()
   {
      std::cout << mCode << " : " << mLenght << " : ";
      for (int index = mLenght-1; index >= 0;--index)
      {
         char temp = ((mCode >> index) & 1) ? '1' : '0';
         std::cout << temp;
      }
   }
   void OutputSymbol()
   {
      std::cout << mSymbol;
   }

private:
   CSymbol() {} // Don't use that
};

// **************************************************************

// **************************************************************

template <class T>
class CCodeEntry {
public:
   CCodeEntry()
   {
      mProbability = 0;
   };
   CCodeEntry(T symbol, double probability)
   {
      mSymbols.push_back(symbol);
      mProbability = probability;
   };
   CCodeEntry(CCodeEntry<T> &ce1, CCodeEntry<T> &ce2)
   {
      mProbability = ce1.mProbability;
      mProbability += ce2.mProbability;


      typename std::list<CSymbol<T> >::iterator it;
      // Adds all symbols of the first code entry: < 0 branch >
      for (it = ce1.mSymbols.begin(); it != ce1.mSymbols.end();++it)
      {
         // Increases the length of the code, no need to add a zero
         ++(it->mLenght);
         mSymbols.push_back(*it);
      }
      // Adds all symbols of the second code entry: < 1 branch >
      for (it = ce2.mSymbols.begin(); it != ce2.mSymbols.end();++it)
      {
         // Increases the length of the code, adds a 1
         ++(it->mLenght);
         (it->mCode) |= (1 << (it->mLenght-1));
         mSymbols.push_back(*it);
      }
   }

   ~CCodeEntry() {}

   // Conditional operators - implemented for stl::list::sort
   // ********************************************************
   bool operator>(CCodeEntry<T> &x)
   {
      return (mProbability > x.mProbability);
   }
   bool operator<(CCodeEntry<T> &x)
   {
      return (mProbability < x.mProbability);
   }
   bool operator>=(CCodeEntry<T> &x)
         {
      return (mProbability >= x.mProbability);
   }
   bool operator<=(CCodeEntry<T> &x)
         {
      return (mProbability <= x.mProbability);
   }
   // ********************************************************

   // Member access functions
   // ********************************************************
   void SetProbability(double probability)
   {
      mProbability = probability;
   }

   void SetSymbol(T symbol)
   {
      mSymbols.clear();
      mSymbols.push_back(symbol);
   }

   double GetProbability()
   {
      return mProbability;
   }

   std::list<CSymbol<T> > &GetSymbols()
   {
      return mSymbols;
   }

   // Debugging functions
   // ********************************************************
   void OutputSymbols()
   {
      typename std::list<CSymbol<T> >::iterator it;
      for (it = mSymbols.begin(); it != mSymbols.end(); ++it)
      {
         std::cout << it->mSymbol << " ";
      }
   }

private:
   std::list<CSymbol<T> >  mSymbols;
   double                  mProbability;

};

// **************************************************************

// **************************************************************

template <class T>
class HuffmanResolver {
public:
   HuffmanResolver() {}
   ~HuffmanResolver() {}

   void AddCodeEntry(CCodeEntry<T> &code_entry)
   {
      mCodeList.push_back(code_entry);
   }

   bool IsResolved()
   {
      return (mCodeList.size() == 1);
   }

   bool IsComplete()
   {
      double prob = 0;

      typename std::list<CCodeEntry<T> >::iterator it;
      for (it = mCodeList.begin(); it != mCodeList.end(); ++it)
      {
         prob += it->GetProbability();
      }
      return (prob == 1.0);
   }

   double Merge()
   {
      double rval = 0;
      if (!IsResolved())
      {
         mCodeList.sort();

         typename std::list<CCodeEntry<T> >::iterator it1 = mCodeList.begin();
         typename std::list<CCodeEntry<T> >::iterator it2 = it1;
         it2++;

         CCodeEntry<char> code_entry(*(it1), *(it2));
         mCodeList.pop_front();
         mCodeList.pop_front();
         mCodeList.push_back(code_entry);
      }
      return rval;
   }

   void Reset()
   {
      mCodeList.clear();
   }

   void OutputCodeList()
   {
      typename std::list<CCodeEntry<T> >::iterator it;
      std::cout << "**************** Code List ******************" << std::endl;
      for (it = mCodeList.begin(); it != mCodeList.end(); ++it)
      {
         std::cout << "Probability: " << it->GetProbability() << " : ";
         it->OutputSymbols();
         std::cout << std::endl;
      }
   }

   void OutputCodes()
   {
      if (IsResolved())
      {
         typename std::list<CCodeEntry<T> >::iterator pof = mCodeList.begin();

         // For all codes in the only code entry left (after it's resolved)
         typename std::list<CSymbol<T> >::iterator it = pof->GetSymbols().begin();
         for (; it != pof->GetSymbols().end();++it)
         {
            it->OutputSymbol();
            std::cout << " : ";
            it->OutputCode();
            std::cout << std::endl;
         }

      }
   }

private:
   std::list<CCodeEntry<T> > mCodeList;
};




#endif /* HUFFMAN_HPP_ */
