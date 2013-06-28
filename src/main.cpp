
#include "huffman.hpp"

int
main(int argc, char *argv[])
{
   const int    numberOfCodes                  = 7;
   const char   codeNames[numberOfCodes]       = { 'B',  'A',  'E',  'D',  'C',  'F',  'G'};
   const double codeProbability[numberOfCodes] = {0.01, 0.48, 0.05, 0.10, 0.15, 0.20, 0.01};

   HuffmanResolver<char> hr;
   CCodeEntry<char>      code;

   for (int i = 0; i<numberOfCodes;++i)
   {
      code.SetProbability(codeProbability[i]);
      code.SetSymbol(codeNames[i]);

      hr.AddCodeEntry(code);
   }

   if (hr.IsComplete())
   {
      std::cout << "Codes are complete" << std::endl;
   }

   // Start Merging Symbols
   // -----------------------------------------
   while (!hr.IsResolved())
   {
      hr.Merge();
      hr.OutputCodeList();
   }
   hr.OutputCodes();

   std::cout << "Done !!!" << std::endl;

   return 0;
}

