#define FILL_GDT_ENTRY(n, l015, b015, b1623, ac, gr, b2431) \
                gdt[n].limit_0_15 = l015; \
                gdt[n].base_0_15 = b015; \
                gdt[n].base_16_23 = b1623; \
                gdt[n].access = ac; \
                gdt[n].granularity = gr; \
                gdt[n].base_24_31 = b2431;

struct GDT
{
   unsigned short limit_0_15; 
   unsigned short base_0_15;  
   unsigned char base_16_23;
   unsigned char access;  
   unsigned char granularity;  
   unsigned char base_24_31;  
} __attribute__((packed));

struct GDT_PTR
{
   unsigned short gdt_size;
   struct GDT* gdt_addr;  
} __attribute__((packed));

struct GDT gdt[5];
struct GDT_PTR gdt_ptr;

extern void load_gdt(struct GDT*);

void init_gdt()
{
        FILL_GDT_ENTRY(0,0,0,0,0,0,0);

        FILL_GDT_ENTRY(1,0xFFFF,0,0,0b10011010,0b11001111,0); //ring0 code
        FILL_GDT_ENTRY(2,0xFFFF,0,0,0b10010010,0b11001111,0); //ring0 data

        FILL_GDT_ENTRY(3,0xFFFF,0,0,0b11111010,0b11001111,0); //ring3 code
        FILL_GDT_ENTRY(4,0xFFFF,0,0,0b11110010,0b11001111,0); //ring3 data

        gdt_ptr.gdt_size = sizeof(gdt) - 1;
        gdt_ptr.gdt_addr = (struct GDT*)&gdt;
        load_gdt((struct GDT*)&gdt_ptr);
        print("Loaded GDT.\n", 15);
}
