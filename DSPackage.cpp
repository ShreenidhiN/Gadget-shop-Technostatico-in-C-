#include<iostream>
using namespace std;
#include<cstring>
#include<fstream>
#include<string>
#include "stdlib.h"

//the functions used
void display_cart();
void addToCart(struct ShoppingCart *a);
void insert_mll_TABLET();
float getTotal();
void removeItem(char prno[4]);
void emptyCart();

// creating different structs for the required gadgets and shop cart
//struct for mobile
struct MOBILE
{
    int qty;
    char pno[4],brand[20], model[20], details[50];
    float price;
    MOBILE *Next_qty;
    MOBILE *Next_brand;
    MOBILE *Next_pno;
    MOBILE *Next_price;
}*head_mpno = 0, *head_mbrand = 0, *head_mqty = 0, *head_mprice = 0;
//struct for tablet
struct TABLET
{
    char pno[4];int qty;
    char brand[20], model[20], details[50];
    float price;
    TABLET *Next_qty;
    TABLET *Next_brand;
    TABLET *Next_pno;
    TABLET *Next_price;
}*head_tqty = 0,*head_tbrand = 0,*head_tpno = 0,*head_tprice = 0;
//struct for laptop
struct LAPTOP
{
    char pno[4];int qty;
    char brand[20], model[20], details[70];
    float price;
    LAPTOP *Next_qty;
    LAPTOP *Next_brand;
    LAPTOP *Next_pno;
    LAPTOP *Next_price;
}*head_lqty = 0,*head_lbrand = 0,*head_lpno = 0,*head_lprice = 0;
float cartTotal = 0;
//struct for shopping cart
struct ShoppingCart
{
    char pno[4];
    int qnty;
    char brand[20], model[20];
    float cost, net_cost;
    struct ShoppingCart *next;
}*cart_top = NULL;


ofstream fp;
MOBILE m[9];
TABLET t[9];
LAPTOP l[9];
// to write the products into file
void input(char cat,int i,char p[4],char b[20],char mod[20],float pri, int q, char d[50])
{
    if(cat=='m')
     {
         fp.open("C:CodeBlocksPrograms\\shopfile\\mobiles.txt",ios::out|ios::app);
        //file for mobiles
        strcpy(m[i].pno,p);
        strcpy(m[i].brand,b);
        strcpy(m[i].model,mod);
        m[i].price=pri;
        m[i].qty=q;
        strcpy(m[i].details,d);
        fp.write((char*)&m[i],sizeof(m[i]));
     }
    else if(cat=='t')
    {
        fp.open("C:CodeBlocksPrograms\\shopfile\\tablets.txt",ios::out|ios::app);
        //file for tablets
        strcpy(t[i].pno,p);
        strcpy(t[i].brand,b);
        strcpy(t[i].model,mod);
        t[i].price=pri;
        t[i].qty=q;
        strcpy(t[i].details,d);
        fp.write((char*)&t[i],sizeof(t[i]));
    }
    else if(cat=='l')
    {
        fp.open("C:CodeBlocksPrograms\\shopfile\\laptops.txt",ios::out|ios::app);
        //file for laptops
        strcpy(l[i].pno,p);
        strcpy(l[i].brand,b);
        strcpy(l[i].model,mod);
        l[i].price=pri;
        l[i].qty=q;
        strcpy(l[i].details,d);
        fp.write((char*)&l[i],sizeof(l[i]));
    }

        fp.close();
}

void insert_mll_MOBILE()
{
    ifstream f;
    MOBILE mm[9];
    f.open("C:CodeBlocksPrograms\\shopfile\\mobiles.txt",ios::in);
    int i=0;
    //read from file and put into multi linked list
    while(!f.eof()&&i<9)
    {
        MOBILE *pro = new MOBILE;
        f.read((char*)&mm[i],sizeof(MOBILE));
        // put into linked list
        strcpy(pro->pno , mm[i].pno );
        strcpy(pro->brand,mm[i].brand) ;
        strcpy(pro->model , mm[i].model) ;
        pro->price = mm[i].price  ;
        pro->qty = mm[i].qty ;
        strcpy(pro->details , mm[i].details ) ;
        //product number as head
        if (head_mpno == 0)
        {
            head_mpno = head_mbrand = head_mqty = head_mprice = pro;
            pro->Next_pno = pro->Next_brand = pro->Next_qty = pro->Next_price = 0;
        }
        else
        {
            MOBILE* p = head_mpno;
            MOBILE* q = head_mbrand;
            MOBILE* r = head_mprice;
            MOBILE* s = head_mqty;
            MOBILE *pprev=0, *qprev=0, *rprev=0, *sprev=0;

            while (p != 0 && strcmp(p->pno, pro->pno)<0)
            {
                pprev = p;
                p = p->Next_pno;
            }
            if (pprev == 0)
            {
                pro->Next_pno = head_mpno;
                head_mpno = p;
            }
            else
            {
                pprev->Next_pno = pro;
                pro->Next_pno = p;
            }
            //brand as head
            while (q != 0 && strcmp(q->brand,pro->brand)<0)
            {
                qprev = q;
                q = q->Next_brand;
            }
            if (qprev == 0)
            {
                pro->Next_brand = head_mbrand;
                head_mbrand = pro;
            }
            else
            {
                qprev->Next_brand = pro;
                pro->Next_brand = q;
            }
            // price as head
            while (r != 0 && r->price <pro->price)
            {
                rprev = r;
                r = r->Next_price;
            }
            if (rprev == 0)
            {
                pro->Next_price = head_mprice;
                head_mprice = pro;
            }
            else
            {
                rprev->Next_price = pro;
                pro->Next_price = r;
            }

            while (s != 0 && s->qty <pro->qty)
            {
                sprev = s;
                s = s->Next_qty;
            }
            if (sprev == 0)
            {
                pro->Next_qty = head_mqty;
                head_mqty = pro;
            }
            else
            {
                sprev->Next_qty = pro;
                pro->Next_qty = s;
            }
        }
            i++;
    }
    f.close();
}
int displayMobile()
{
    cout<<"\n\nDisplay Mobiles :\n\n";
    struct MOBILE *p,*q,*r,*s;
    p = head_mpno;
    cout<<"\nPNO\tBRAND\tMODEL";
    //to display all the details based on product number sort
    while(p!=NULL)
    {
        cout<<"\n";
        cout<<p->pno<<"\t"<<p->brand<<"\t"<<p->model<<"\tPRICE(RS):"<<p->price<<"\tSTOCK LEFT:"<<p->qty<<"\tDETAILS:"<<p->details<<"\n";
        p = p->Next_pno;
    }
    q = head_mbrand;

    cout<<"\nTO SORT :1 BY BRAND, 2 BY PRICE, 3 BY QUANTITY AVAILABILITY. ";
    int n;
    cin>>n;
    switch(n)
    {
     case 1:
    {
    cout<<"\nSORTED BY BRAND";
    // using brand head and sort
    while(q!=NULL)
    {
        cout<<"\n";
        cout<<q->pno<<"\t"<<q->brand<<"\t"<<q->model<<"\tPRICE(RS):"<<q->price<<"\tSTOCK LEFT:"<<q->qty<<"\n";
        q = q->Next_brand;
    }
    break;
    }
     case 2:
    {

    s = head_mprice;
    cout<<"\nSORTED BY PRICE ";
    //using price as head and sort
    while(s!=NULL)
    {
        cout<<"\n";
        cout<<s->pno<<"\t"<<s->brand<<"\t"<<s->model<<"\tPRICE(RS):"<<s->price<<"\tSTOCK LEFT:"<<s->qty<<"\n";
        s = s->Next_price;
    }
    break;
    }
     case 3:
    {

    cout<<"\nSORTED BY QTY:";
    //using stock / quantity as head and sort
    r = head_mqty;
    while(r!=NULL)
    {
        cout<<"\n";
        cout<<r->pno<<"\t"<<r->brand<<"\t"<<r->model<<"\tPRICE(RS):"<<r->price<<"\tSTOCK LEFT:"<<r->qty<<"\n";
        r = r->Next_qty;
    }
    break;
    }
    }
    char ch,opt='y';
    int quantity;
    cout<<"\nPRESS Y-TO ADD PRODUCT TO CART OR PRESS ANY KEY-TO GO BACK TO MENU! :";
    cin>>ch;
    if(ch!='y'&&ch!='Y')
        return(1);

    char prdno[4];
    while(opt=='y'||opt=='Y')
    {
        cout<<"\n\nENTER THE PRODUCT NO AND THE QUANTITY YOU WANT TO ADD TO CART: ";
        //ask customer to add to cart
        cin>>prdno;
        cin>>quantity;
        struct MOBILE *p;
        struct ShoppingCart *s;
        s = new ShoppingCart;
        p = head_mpno;
        int flag =0;
        while(p!=NULL)
        {
            if(strcmp(prdno,p->pno)==0)
            {
                p->qty -= quantity;
                strcpy(s->pno,p->pno);
                strcpy(s->brand,p->brand);
                strcpy(s->model,p->model);
                s->cost = p->price;
                s->qnty = quantity;
                s->net_cost = s->qnty * s->cost;
                s->next=NULL;
                flag=1;
                break;

            }
            p = p->Next_pno;
        }
        // to input valid product number from customer and quantity <= stock availability
        if(flag==1)
            addToCart(s); // add to cart function
        else
            cout<<"\n\tINVALID PRODUCT NO!!!\n";
        cout<<"\nDO YOU WANT TO ADD AGAIN?(Y-YES) : ";
        cin>>opt;
    }

}
void insert_mll_TABLET()
{
    ifstream f;
    TABLET mm[9];
    f.open("C:CodeBlocksPrograms\\shopfile\\tablets.txt",ios::in);
    int i=0;
    while(!f.eof()&&i<9)
    {
        TABLET *pro = new TABLET;
        f.read((char*)&mm[i],sizeof(TABLET));
        //read from file and insertb into multi linked list
        strcpy(pro->pno , mm[i].pno );
        strcpy(pro->brand,mm[i].brand) ;
        strcpy(pro->model , mm[i].model)  ;
        pro->price = mm[i].price  ;
        pro->qty = mm[i].qty ;
        strcpy(pro->details , mm[i].details ) ;

        if (head_tpno == 0)
        {
            head_tpno = head_tbrand = head_tqty = head_tprice = pro;
            pro->Next_pno = pro->Next_brand = pro->Next_qty = pro->Next_price = 0;
        }
        else
        {
            TABLET* p = head_tpno;
            TABLET* q = head_tbrand;
            TABLET* r = head_tprice;
            TABLET* s = head_tqty;
            TABLET *pprev=0, *qprev=0, *rprev=0, *sprev=0;
            // product number as head inserted
            while (p != 0 && strcmp(p->pno, pro->pno)<0)
            {
                pprev = p;
                p = p->Next_pno;
            }
            if (pprev == 0)
            {
                pro->Next_pno = head_tpno;
                head_tpno = p;
            }
            else
            {
                pprev->Next_pno = pro;
                pro->Next_pno = p;
            }
            // brand as head
            while (q != 0 && strcmp(q->brand,pro->brand)<0)
            {
                qprev = q;
                q = q->Next_brand;
            }
            if (qprev == 0)
            {
                pro->Next_brand = head_tbrand;
                head_tbrand = pro;
            }
            else
            {
                qprev->Next_brand = pro;
                pro->Next_brand = q;
            }
            //price as head
            while (r != 0 && r->price <pro->price)
            {
                rprev = r;
                r = r->Next_price;
            }
            if (rprev == 0)
            {
                pro->Next_price = head_tprice;
                head_tprice = pro;
            }
            else
            {
                rprev->Next_price = pro;
                pro->Next_price = r;
            }
            // stock quantity as head
            while (s != 0 && s->qty <pro->qty)
            {
                sprev = s;
                s = s->Next_qty;
            }
            if (sprev == 0)
            {
                pro->Next_qty = head_tqty;
                head_tqty = pro;
            }
            else
            {
                sprev->Next_qty = pro;
                pro->Next_qty = s;
            }
        }
            i++;
    }
    f.close();

}
int displayTablet()
{
    cout<<"\n\nDisplay Laptops :\n\n";
    struct TABLET *p,*q,*r,*s;
    p = head_tpno;
    cout<<"\nPNO\tBRAND\tMODEL";
    // to sort based on product number by default
    while(p!=NULL)
    {
        cout<<"\n";
        cout<<p->pno<<"\t"<<p->brand<<"\t"<<p->model<<"\tPRICE(RS):"<<p->price<<"\tSTOCK LEFT:"<<p->qty<<"\tDETAILS:"<<p->details<<"\n";
        p = p->Next_pno;
    }
    q = head_tbrand;
    cout<<"\nTO SORT :1 BY BRAND, 2 BY PRICE, 3 BY QUANTITY AVAILABILITY. ";
    // as customer's choice to sort by
    int n;
    cin>>n;
    switch(n)
    {
     case 1:
    {cout<<"\nSORTED BY BRAND";
    // using brand as head sort and display
    while(q!=NULL)
    {
        cout<<"\n";
        cout<<q->pno<<"\t"<<q->brand<<"\t"<<q->model<<"\tPRICE(RS):"<<q->price<<"\tSTOCK LEFT:"<<q->qty<<"\n";
        q = q->Next_brand;
    }
    break;
    }
     case 2:
    {
     s = head_tprice;
    cout<<"\nSORTED BY PRICE:";
    // using price as head sort and display
    while(s!=NULL)
    {
        cout<<"\n";
        cout<<s->pno<<"\t"<<s->brand<<"\t"<<s->model<<"\tPRICE(RS):"<<s->price<<"\tSTOCK LEFT:"<<s->qty<<"\n";
        s = s->Next_price;
    }
    break;
    }
     case 3:
    {

    cout<<"\nSORTED BY AVAILABLE STOCK:";
    // using stock as head sort and display
    r = head_tqty;
    while(r!=NULL)
    {
        cout<<"\n";
        cout<<r->pno<<"\t"<<r->brand<<"\t"<<r->model<<"\tPRICE(RS):"<<r->price<<"\tSTOCK LEFT:"<<r->qty<<"\n";
        r = r->Next_qty;
    }
    break;
    }
    }
    char ch,opt='y';
    int quantity;
    cout<<"\nPRESS Y-TO ADD PRODUCT TO CART OR PRESS ANY KEY-TO GO BACK TO MENU! :";
    cin>>ch;
    // ask customer to choose product and add to acrt or go back
    if(ch!='y'&&ch!='Y')
        return(1);

    char prdno[4];
    while(opt=='y'||opt=='Y')
    {
        cout<<"\n\nENTER THE PRODUCT NO AND THE QUANTITY YOU WANT TO ADD TO CART: ";
        cin>>prdno;
        cin>>quantity;
        struct TABLET *p;
        struct ShoppingCart *s;
        s = new ShoppingCart;
        p = head_tpno;
        int flag=0;
        while(p!=NULL)
        {
            if(strcmp(prdno,p->pno)==0)
            {
                // reducing the stock availability once customer buys it
                p->qty -= quantity;
                // copying all the deatiails for desired product into node to put into cart
                strcpy(s->pno,p->pno);
                strcpy(s->brand,p->brand);
                strcpy(s->model,p->model);
                s->cost = p->price;
                s->qnty = quantity;
                s->net_cost = s->qnty * s->cost;
                s->next=NULL;
                flag=1;
                break;
            }
            p = p->Next_pno;
        }
        if(flag==1)
            addToCart(s); // passing the node and add to cart
        else
            cout<<"\n\tINVALID PRODUCT NO!!!\n"; // ensure customer enters correct product number to purchase
        cout<<"\nDO YOU WANT TO ADD AGAIN?(Y-YES) : ";
        cin>>opt;
    }
}
void insert_mll_LAPTOP()
{
    ifstream f;
    LAPTOP mm[9];
    f.open("C:CodeBlocksPrograms\\shopfile\\laptops.txt",ios::in);
    int i=0;
    while(!f.eof()&&i<9)
    {
        LAPTOP *pro = new LAPTOP;
        f.read((char*)&mm[i],sizeof(LAPTOP));
        //read from file and put into multi linked list
        strcpy(pro->pno , mm[i].pno );
        strcpy(pro->brand,mm[i].brand) ;
        strcpy(pro->model , mm[i].model)  ;
        pro->price = mm[i].price  ;
        pro->qty = mm[i].qty ;
        strcpy(pro->details , mm[i].details ) ;
        //product number as head
        if (head_lpno == 0)
        {
            head_lpno = head_lbrand = head_lqty = head_lprice = pro;
            pro->Next_pno = pro->Next_brand = pro->Next_qty = pro->Next_price = 0;
        }
        else
        {
            LAPTOP* p = head_lpno;
            LAPTOP* q = head_lbrand;
            LAPTOP* r = head_lprice;
            LAPTOP* s = head_lqty;
            LAPTOP *pprev=0, *qprev=0, *rprev=0, *sprev=0;

            while (p != 0 && strcmp(p->pno, pro->pno)<0)
            {
                pprev = p;
                p = p->Next_pno;
            }
            if (pprev == 0)
            {
                pro->Next_pno = head_lpno;
                head_lpno = p;
            }
            else
            {
                pprev->Next_pno = pro;
                pro->Next_pno = p;
            }
            // brand as head
            while (q != 0 && strcmp(q->brand,pro->brand)<0)
            {
                qprev = q;
                q = q->Next_brand;
            }
            if (qprev == 0)
            {
                pro->Next_brand = head_lbrand;
                head_lbrand = pro;
            }
            else
            {
                qprev->Next_brand = pro;
                pro->Next_brand = q;
            }
            // price as head
            while (r != 0 && r->price <pro->price)
            {
                rprev = r;
                r = r->Next_price;
            }
            if (rprev == 0)
            {
                pro->Next_price = head_lprice;
                head_lprice = pro;
            }
            else
            {
                rprev->Next_price = pro;
                pro->Next_price = r;
            }
            // stock quantity as head
            while (s != 0 && s->qty <pro->qty)
            {
                sprev = s;
                s = s->Next_qty;
            }
            if (sprev == 0)
            {
                pro->Next_qty = head_lqty;
                head_lqty = pro;
            }
            else
            {
                sprev->Next_qty = pro;
                pro->Next_qty = s;
            }
        }
            i++;
    }
    f.close();
}
int displayLaptop()
{
    cout<<"\n\nDisplay Laptops :\n\n";
    struct LAPTOP *p,*q,*r,*s;
    p = head_lpno;
    cout<<"\nPNO\tBRAND\tMODEL";
    // default display by sorted product number order
    while(p!=NULL)
    {
        cout<<"\n";
        cout<<p->pno<<"\t"<<p->brand<<"\t"<<p->model<<"\tPRICE(RS):"<<p->price<<"\tSTOCK LEFT:"<<p->qty<<"\tDETAILS:"<<p->details<<"\n";
        p = p->Next_pno;
    }

    cout<<"\nTO SORT :1 BY BRAND, 2 BY PRICE, 3 BY QUANTITY AVAILABILITY. ";
    int n;
    cin>>n;
    switch(n)
    {
        case 1:
        {
            q = head_lbrand;
            cout<<"\nSORTED BY BRAND";
            // using brand as head sort and display
            while(q!=NULL)
            {
                cout<<"\n";
                cout<<q->pno<<"\t"<<q->brand<<"\t"<<q->model<<"\tPRICE(RS):"<<q->price<<"\tSTOCK LEFT:"<<q->qty<<"\n";
                q = q->Next_brand;
            }
            break;
        }
        case 2:
        {
            s = head_lprice;
            cout<<"\nSORTED BY PRICE:";
            // using price as head sort and display
            while(s!=NULL)
            {
                cout<<"\n";
                cout<<s->pno<<"\t"<<s->brand<<"\t"<<s->model<<"\tPRICE(RS):"<<s->price<<"\tSTOCK LEFT:"<<s->qty<<"\n";
                s = s->Next_price;
            }
            break;
        }
        case 3:
        {
            cout<<"\nSORTED BY QTY:";
            // using quantity as head sort and display
            r = head_lqty;
            while(r!=NULL)
            {
                cout<<"\n";
                cout<<r->pno<<"\t"<<r->brand<<"\t"<<r->model<<"\tPRICE(RS):"<<r->price<<"\tSTOCK LEFT:"<<r->qty<<"\n";
                r = r->Next_qty;
            }
            break;
        }
    }
    char ch,opt='y';
    int quantity;
    cout<<"\nPRESS Y-TO ADD PRODUCT TO CART OR PRESS ANY KEY-TO GO BACK TO MENU! :";
    cin>>ch;
    //ask customer to add to cart or go back
    if(ch!='y'&&ch!='Y')
        return(1);

    char prdno[4];
    while(opt=='y'||opt=='Y')
    {
        cout<<"\n\nENTER THE PRODUCT NO AND THE QUANTITY YOU WANT TO ADD TO CART: ";
        cin>>prdno;
        cin>>quantity;
        struct LAPTOP *p;
        struct ShoppingCart *s;
        s = new ShoppingCart;
        p = head_lpno;
        int f=0;
        while(p!=NULL)
        {
            if(strcmp(prdno,p->pno)==0)
            {
                p->qty -= quantity; //reducing stock once bought by customer
                strcpy(s->pno,p->pno);
                strcpy(s->brand,p->brand);
                strcpy(s->model,p->model);
                s->cost = p->price;
                s->qnty = quantity;
                s->net_cost = s->qnty * s->cost;
                s->next=NULL;
                f=1;
                break;
            }
            p = p->Next_pno;
        }
        if(f==1)
            addToCart(s);
        else
            cout<<"\nINVALID PRODUCT NUMBER !\n"; // ensure correct product number by customer
        cout<<"\nDO YOU WANT TO ADD AGAIN?(Y-YES) : ";
        cin>>opt;

    }
    return 0;
}
void addToCart(struct ShoppingCart *s)
{
    // funtion in which products are added to cart
    // insert by stack implementation LIFO
     if(cart_top==NULL)
        cart_top=s;
     else
    {
        s->next = cart_top;
        cart_top = s;

    }
 }
void display_cart()
{
    ShoppingCart *s;
    s = cart_top;
    if(cart_top!=NULL)
    {
        cout<<"\nSHOPPING CART :\n";
        cout<<"PDT NO\tBRAND\tMODEL\t\tCOST\tQUANTITY\tNETCOST\n";
        //display all products in cart
        while(s!=NULL)
        {
            cout<<s->pno<<"\t"<<s->brand<<"\t"<<s->model<<"\t\t"<<s->cost<<"\t"<<s->qnty<<"\t"<<s->net_cost<<"\n";
            s=s->next;
        }
        char ch='y',prdno[4];
        int opt;
        // display grand total of cart
        cout<<"\nGRAND TOTAL OF YOUR CART : "<<getTotal()<<" Rs\n";
        cout<<"\nDO YOU WANT TO MODIFY CART?[Y-YES/ANY KEY-NO] : ";
        cout<<"\nPRESS 1.TO DELETE ITEM FROM CART\n2.EMPTY WHOLE CART\n3.EXIT THIS WINDOW";
        int f=0;
        while(ch=='y'||ch=='Y')
        {
            cout<<"\nENTER YOUR CHOICE:";
            cin>>opt;
            if(opt==1)
            {
                cout<<"\nENTER THE PRODUCT NUMBER TO BE DELETED : ";
                //modify cart
                cin>>prdno;
                removeItem(prdno);
            }
            else if(opt==2)
            {
                emptyCart(); //empty entire cart
                f = 1;
            }
            else
                f=2;
            if(f==0)
            {
                cout<<"\nDO YOU WANT TO CONTINUE? [Y-YES/ANY KEY-NO] : ";
                cin>>ch;
            }
            else
                ch='n';
         }
    }
    else
        cout<<"\nCART IS EMPTY !!\n";
}
float getTotal()
{
    struct ShoppingCart *sc;
    sc = cart_top;
    float cartTotal = 0.0;
    // to calculate grand total of cart
    while(sc!=NULL)
    {
        cartTotal += sc->net_cost;
        sc = sc->next;
    }
    return cartTotal;
}
void removeItem(char prno[4])
{
    //to delete a product in cart
    struct ShoppingCart *sc,*prevsc,*temp;
    prevsc = NULL;
    temp =  NULL;
    sc = cart_top;
    MOBILE *m = head_mpno;
    TABLET *t = head_tpno;
    LAPTOP *l = head_lpno;
    while(sc!=NULL)
    {
        if(strcmp(sc->pno,prno)==0)
        {
            while(m!=NULL)
            {
                if(strcmp(prno,m->pno)==0)
                    m->qty += sc->qnty; // add stock back to gadget if discarded from cart
                m = m->Next_pno;
            }
            while(l!=NULL)
            {
                if(strcmp(prno,l->pno)==0)
                    l->qty += sc->qnty;
                l = l->Next_pno;
            }
            while(t!=NULL)
            {
                if(strcmp(prno,t->pno)==0)
                    t->qty += sc->qnty;
                t = t->Next_pno;
            }
            if(sc == cart_top)
            {
                cart_top = sc->next;
                delete sc;
            }
            else
            {
                temp = sc;
                prevsc->next = sc->next;
                delete temp;
                break;
            }
        }
        prevsc = sc;
        sc = sc->next;
    }
}

void emptyCart()
{
    // empty the entire cart
    struct ShoppingCart *sc,*temp;
    sc = cart_top;
    while(sc!=NULL)
    {
        temp = sc->next;
        delete sc;
        sc = temp;
    }
    cart_top = NULL;
}

void inputAllFile()
{
    //enter mobile details into cart
    input('m',0,"BC1","Samsung","GalaxyS10",61327,35,"8GB-128GBstorage-6.10inch-157gms-Android9Pie");
    input('m',1,"CD2","Samsung","GalaxyJ7",13000,45,"4GB-32GBstorage-5.5inch-150gms-AndroidOreo");
    input('m',2,"DE3","Samsung","GalaxyM10",8990,15,"3GB-32GBstorage-6.22inch-163gms-AndroidOreo");
    input('m',3,"EF4","Samsung","Note9",84900,26,"6GB-128GBstorage-6.4inch-160gms-AndroidOreo");
    input('m',4,"GH5","Samsung","GalaxyM30",14990,46,"4Gb-64GBstorage-6.4inch-160gms-AndroidOreo");
    input('m',5,"HI6","Apple","XsMAX",131000,31,"4GB-512GBstorage-6.5inch-209gms-IOS12");
    input('m',6,"IJ7","Apple","6S",27000,15,"3GB-64Storage-4.7inch-192gms-IOSV9");
    input('m',7,"JK8","Apple","XR",67999,25,"3GB-64GBstorage-6.10inch-194gms-IOS");
    input('m',8,"KL9","Apple","X",98000,50,"3GB-64GBstorage-5.8inch-194gms-IOS");
    //enter laptop details to cart
    input('l',0,"A11","Lenovo","IdeaPad330",43990,15,"Intelcore:I5-8Gen-16inch-6GB/2TB-HDD/DOS/2GB/Platinumgrey-2.2kg");
    input('l',1,"A12","Lenovo","IdeaPad320",25490,60,"Intelcore:I3-6Gen-14inch-4GB/1TB-HDD/Windows10/OnyxBlack-2.2kg");
    input('l',2,"A13","Lenovo","IdeaPad530",82990,55,"Intelcore:I5-8Gen-14inch-8GB/512GB-SSD/Windows10/MineralGrey-1.67kg");
    input('l',3,"A14","HP","PavilionX360",49900,48,"Intelcore:I3-8Gen-14inch-4GB/1TB+8GB-SSHD/Windows10/NaturalSilver-1.59kg");
    input('l',4,"A15","HP","Q14",32914,25,"Intelcore:I3-7Gen-14inch-4GB/1TB/DOS2.O/JetBlack-1.59kg");
    input('l',5,"A16","HP","Envy13",64594,35,"Intelcore:I3-8Gen-13.3inch-4GB/128GB-Windows10/NaturalSilver-1.5kg");
    input('l',6,"A17","Dell","Vostro3568",45872,20,"Intelcore:I3-6Gen-15.6inch/4GB/1TB-HDD/Windows10/Black-2.18kg");
    input('l',7,"A18","Dell","Inspiron5370",78369,35,"Intelcore:I5-8Gen-13.3inch/8GB/256GB-SSD/Windows10/Silver-1.5kg");
    input('l',8,"A19","Dell","Vostro3478",37949,36,"Intelcore:I3-8Gen-14inch-4GB/1TB HDD/Windows10/Black-2.25kg");
    //insert tablets to cart
    input('t',0,"A10","Samsung","GalaxyS4",50000,38,"4GB-10.5inch-AndroidOreov8.1-singleSim");
    input('t',1,"B21","Samsung","GalaxyA10",19990,45,"4GB-6.4inch-AndroidPie-dualSim");
    input('t',2,"C31","Micromax","CanvasPlex",7999,50,"3GB-8inch-Android5.1-dualSim");
    input('t',3,"D40","Micromax","InfinityN12",9440,36,"3GB-6.2inch-AndroidOreo8.1-dualSim");
    input('t',4,"E51","Lenovo","Tab7",5400,64,"1GB-7inch-AndroidOS7.0-singleSim");
    input('t',5,"F60","Lenovo","Tab3",5535,35,"1GB-7inch-Androidv5.1Lollipop-singleSim");
    input('t',6,"G71","Honor","MediaPad",8999,43,"2GB-8inch-Androidv7.0-singleSim");
    input('t',7,"H81","Acer","One7",4498,45,"1GB-7inch-Androidv6.0Marshmallow-singleSim");
    input('t',8,"I90","Acer","Iconia",3000,40,"1GB-10inch-Android-singleSim");
}

int main()
{
    inputAllFile();
    insert_mll_MOBILE();
    insert_mll_TABLET();
    insert_mll_LAPTOP();
    int choice;
    char ch='y';
    cout<<"\nWELCOME TO TECHNOSTATICO SHOP";
    while(ch=='y'||ch=='Y')
    {
        //choose category from the 3
        cout<<"\nCATEGORIES :";
        cout<<"\n\t 1-MOBILES\n\t 2-TABLETS\n\t 3-LAPTOPS\n\t\ 4-DISPLAY SHOPPING CART\n\t 5-QUIT";
        cout<<"\nENTER THE CATEGORY NUMBER: ";
        cin>>choice;

        switch(choice)
        {
            case 1: displayMobile();
                    break;
            case 2: displayTablet();
                    break;
            case 3: displayLaptop();
                    break;
            case 4: display_cart();
                    break;
            case 5: cout<<"THANK YOU FOR USING!!!";
                    exit(1);
            default: cout<<"WRONG CHOICE ";
                    break;
        }
        cout<<"BACK TO MAIN MENU?[Y-YES/N-NO]";
        cin>>ch;
    }
    return 0;
}
