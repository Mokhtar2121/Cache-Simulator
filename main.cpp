#include <iostream>

#include  <iomanip>

using namespace std;

// fixed parameters
#define		DBG				1
#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)


// defining the following parameters as global
int numberofways;
int numberofblocks;
int indexbits;
int word_offset;

// enum used to determine the cache result
enum cacheResType {MISS=0, HIT=1};

// a block used to store details of the address that we will store in the cache
struct block{
    bool valid;  // hit or miss, false = miss, true = hit
    int tag;    // tag
    int data;   // memory stores (bits)
};



/* The following implements a random number generator */
unsigned int m_w = 0xABABAB55;    /* must not be zero, nor 0x464fffff */
unsigned int m_z = 0x05080902;    /* must not be zero, nor 0x9068ffff */
unsigned int rand_()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
}

unsigned int memGen1()
{
    static unsigned int addr=0;
    return (addr++)%(DRAM_SIZE);
}

unsigned int memGen2()
{
    static unsigned int addr=0;
    return  rand_()%(24*1024);
}

unsigned int memGen3()
{
    return rand_()%(DRAM_SIZE);
}

unsigned int memGen4()
{
    static unsigned int addr=0;
    return (addr++)%(4*1024);
}

unsigned int memGen5()
{
    static unsigned int addr=0;
    return (addr++)%(1024*64);
}

unsigned int memGen6()
{
    static unsigned int addr=0;
    return (addr+=32)%(64*4*1024);
}

// Set Associative Cache Simulator
// This function accepts the memory address for the memory transaction and
// returns whether it caused a cache miss or a cache hit
cacheResType cacheSimSA(block* cache[], unsigned int addr)
{



    int mask1=(pow(2,indexbits)-1); //  a var that will locate the perfect mask we will use to determine the index's bits
    int indexSA =(addr>>(word_offset)) & mask1 ; //index
    int tagSA = (addr >> (word_offset+indexbits)); //tag




    int counter=0; // counter to check if the set is full
    int free_spot=0; // check if there is a free spot we can use to store the address in case of miss


    // checking for a hit
    for ( int i=0; i<numberofways; i++ ) {
        if (cache[indexSA][i].valid == true) {
            counter++;

            if (cache[indexSA][i].tag == tagSA)
                return HIT;

        } else free_spot=i;

    }




      if (counter>=numberofways) { // checking for a capacity conflict

          int repleced_addr =rand_()%numberofways; // choosing a random cell

          cache[indexSA][repleced_addr].valid= true;   // replacing it
          cache[indexSA][repleced_addr].tag= tagSA;
          return MISS;

      } else {  // inserting an address in the free spot

          cache[indexSA][free_spot].valid= true;
          cache[indexSA][free_spot].tag= tagSA;
        //
        return MISS;
    }


}

// msg that will be printed for debugging issues
char *msg[2] = {"Miss","Hit"};

#define		NO_OF_Iterations	1000000

int main()
{   // data structure to represent the cache
    block **cache;


    cout<<"\nExperement 1:\nWith a number of ways fixed to 4, we will calculate the hit ratio with different cache line sizes: \n";

    int Cache_line_size [] = {16, 32, 64, 128};  //bytes.
    for (int i =0; i<4; i++) {

        cout<<"\nTesting for cache with size: "<<Cache_line_size[i]<<endl;

        numberofways= 4; //number of ways
        numberofblocks= (CACHE_SIZE/ (numberofways*Cache_line_size[i])); //number of blocks
        indexbits=log2(numberofblocks);//index

        word_offset=(log2(Cache_line_size[i])); // change 4 to vary with # of ways

        cache = reinterpret_cast<block **>(new block[numberofblocks]);
    for(int i = 0; i < numberofblocks; ++i)
        cache[i] = new block [numberofways];
    double hit = 0;
    cacheResType r;

    unsigned int addr;

    for(int inst=0;inst<NO_OF_Iterations;inst++)
    {
        addr = memGen1();
        r = cacheSimSA(cache, addr);
        if(r == HIT) hit++;


    }

    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    cout << "Hit ratio for  = memGen1(): " <<  (100*hit/NO_OF_Iterations)<< endl;

    hit =0;

    cache = reinterpret_cast<block **>(new block[numberofblocks]);

    for(int i = 0; i < numberofblocks; ++i)
        cache[i] = new block [numberofways];

    for(int inst=0;inst<NO_OF_Iterations;inst++)
    {
        addr = memGen2();
        r = cacheSimSA(cache,addr);
        if(r == HIT) hit++;

    }

    cout << "Hit ratio for  = memGen2(): " << double (100*hit/NO_OF_Iterations)<< endl;
    hit =0;

    cache = reinterpret_cast<block **>(new block[numberofblocks]);

    for(int i = 0; i < numberofblocks; ++i)
        cache[i] = new block [numberofways];

    for(int inst=0;inst<NO_OF_Iterations;inst++)
    {
        addr = memGen3();
        r = cacheSimSA(cache, addr);
        if(r == HIT) hit++;

    }

    cout << "Hit ratio for  = memGen3(): " <<  100*hit/NO_OF_Iterations<< endl;
    hit =0;

    cache = reinterpret_cast<block **>(new block[numberofblocks]);

    for(int i = 0; i < numberofblocks; ++i)
        cache[i] = new block [numberofways];

    for(int inst=0;inst<NO_OF_Iterations;inst++)
    {
        addr = memGen4();
        r = cacheSimSA(cache, addr);
        if(r == HIT) hit++;

    }
    cout << "Hit ratio for  = memGen4(): " << double (100*hit/NO_OF_Iterations)<< endl;
    hit =0;

    cache = reinterpret_cast<block **>(new block[numberofblocks]);

    for(int i = 0; i < numberofblocks; ++i)
        cache[i] = new block [numberofways];

    for(int inst=0;inst<NO_OF_Iterations;inst++)
    {
        addr = memGen5();
        r = cacheSimSA(cache, addr);
        if(r == HIT) hit++;

    }
    cout << "Hit ratio for  = memGen5(): " << double (100*hit/NO_OF_Iterations)<< endl;
    hit =0;

    cache = reinterpret_cast<block **>(new block[numberofblocks]);

    for(int i = 0; i < numberofblocks; ++i)
        cache[i] = new block [numberofways];

    for(int inst=0;inst<NO_OF_Iterations;inst++)
    {
        addr = memGen6();
        r = cacheSimSA(cache,addr);
        if(r == HIT) hit++;

    }
    cout << "Hit ratio for  = memGen6(): " << double (100*hit/NO_OF_Iterations)<< endl;

    }


    cout<<"\nExperement 2:\nWith a cache line size fixed to 16 bytes, we will calculate the hit ratio with different number of ways: \n";

     int way [] = {1, 2, 4 , 8};
    for (int i =0; i<4; i++) {

        cout<<"\nTesting for ways n= : "<<way[i]<<endl;

        numberofways= way[i]; //number of ways
        numberofblocks= (CACHE_SIZE/ (numberofways*16)); //number of blocks
        indexbits=log2(numberofblocks);//index

        word_offset=(log2(16)); // change 4 to vary with # of ways

        cache = reinterpret_cast<block **>(new block[numberofblocks]);
        for(int i = 0; i < numberofblocks; ++i)
            cache[i] = new block [numberofways];
        double hit = 0;
        cacheResType r;

        unsigned int addr;

        for(int inst=0;inst<NO_OF_Iterations;inst++)
        {
            addr = memGen1();
            r = cacheSimSA(cache,addr);
            if(r == HIT) hit++;


        }

        std::cout << std::fixed;
        std::cout << std::setprecision(4);
        cout << "Hit ratio for  = memGen1(): " <<  (100*hit/NO_OF_Iterations)<< endl;

        hit =0;

        cache = reinterpret_cast<block **>(new block[numberofblocks]);

        for(int i = 0; i < numberofblocks; ++i)
            cache[i] = new block [numberofways];

        for(int inst=0;inst<NO_OF_Iterations;inst++)
        {
            addr = memGen2();
            r = cacheSimSA(cache, addr);
            if(r == HIT) hit++;

        }

        cout << "Hit ratio for  = memGen2(): " << double (100*hit/NO_OF_Iterations)<< endl;
        hit =0;

        cache = reinterpret_cast<block **>(new block[numberofblocks]);

        for(int i = 0; i < numberofblocks; ++i)
            cache[i] = new block [numberofways];

        for(int inst=0;inst<NO_OF_Iterations;inst++)
        {
            addr = memGen3();
            r = cacheSimSA(cache,addr);
            if(r == HIT) hit++;

        }

        cout << "Hit ratio for  = memGen3(): " <<  100*hit/NO_OF_Iterations<< endl;
        hit =0;

        cache = reinterpret_cast<block **>(new block[numberofblocks]);

        for(int i = 0; i < numberofblocks; ++i)
            cache[i] = new block [numberofways];

        for(int inst=0;inst<NO_OF_Iterations;inst++)
        {
            addr = memGen4();
            r = cacheSimSA(cache,addr);
            if(r == HIT) hit++;

        }
        cout << "Hit ratio for  = memGen4(): " << double (100*hit/NO_OF_Iterations)<< endl;
        hit =0;

        cache = reinterpret_cast<block **>(new block[numberofblocks]);

        for(int i = 0; i < numberofblocks; ++i)
            cache[i] = new block [numberofways];

        for(int inst=0;inst<NO_OF_Iterations;inst++)
        {
            addr = memGen5();
            r = cacheSimSA(cache,addr);
            if(r == HIT) hit++;

        }
        cout << "Hit ratio for  = memGen5(): " << double (100*hit/NO_OF_Iterations)<< endl;
        hit =0;

        cache = reinterpret_cast<block **>(new block[numberofblocks]);

        for(int i = 0; i < numberofblocks; ++i)
            cache[i] = new block [numberofways];

        for(int inst=0;inst<NO_OF_Iterations;inst++)
        {
            addr = memGen6();
            r = cacheSimSA(cache,addr);
            if(r == HIT) hit++;

        }
        cout << "Hit ratio for  = memGen6(): " << double (100*hit/NO_OF_Iterations)<< endl;

    }


    cout<<"\n\nTesting for validation : "<<endl;

    numberofways= 4; //number of ways
    numberofblocks= (CACHE_SIZE/ (numberofways*16)); //number of blocks
    indexbits=log2(numberofblocks);//index

    word_offset=(log2(16)); // change 4 to vary with # of ways

    cache = reinterpret_cast<block **>(new block[numberofblocks]);

    cout<< "\n\nWhat makes us sure about the results is the following tests cases: \n"
           "We will pass the address  0x007a1204 to the cache simulator after clearing it. So, the result will be miss: \n";



    unsigned int addr= 0x007a1204;
    cacheResType r;
    for(int i = 0; i < numberofblocks; ++i)
        cache[i] = new block [numberofways];



    r = cacheSimSA(cache, addr);
    cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[r] <<")\n";

    cout<<"But, when passing  0x007a1201 now, the result will be Hit as the cache simulator located all addreses near  0x007a1200: \n";
    addr= 0x007a1201;
    r = cacheSimSA(cache,addr);
    cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[r] <<")\n";
    cout<<"Then let's try 0x007a1210: \n";
    addr= 0x007a1210;
    r = cacheSimSA(cache,addr);
    cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[r] <<")\n";
    cout<<"Miss for sure, lets do 0x007a1211, it must be HIT since cache located after the previous address  : \n";
    addr= 0x007a1211;
    r = cacheSimSA(cache,addr);
    cout <<"0x" << setfill('0') << setw(8) << hex << addr <<" ("<< msg[r] <<")\n";


}