/*
This function prints a ipaddr_t variable on the terminal in the following format
octet1.octet2.octet3.octet4
No spaces, no new line in the end, octets are separated by a dot.
Inputs:
  ip - ipaddr_t variable that needs to be printed
*/

/*adding struct ipaddr*/
typedef struct {
   int octet1;
   int octet2
   int octet3
   int octet4
} ipaddr_t;

void print_ipaddr(ipaddr_t ip)
{
  printf("%d.%d.%d.%d", ip.octet1, ip.octet2, ip.octet3, ip.octet4); /*maybe can have ipaddr_t ip = {}?*/
}

/*
An IP address is valid if all 4 octets have values between 0 and 255(inclusive).
The function checks if the input ip address is valid.
Inputs:
  ip - ipaddr_t input IP address variable
Return:
  1 - if input ip is valid
  0 - otherwise
*/
int is_valid(ipaddr_t ip)
{
    scanf("");
    /*to check each octet*/
    if (ip.octet1 >= 0 && ip.octet1 <= 255 &&
    ip.octet2 >= 0 && ip.octet2 <= 255 && 
    ip.octet3 >=0 && octet3 <= 255 && 
    ip.octet4 >= 0 && ip.octet4 <= 255){
      
      return 1; /* if input ip is valid*/
    } else {
      return 0; /*if input ip is invalid*/
    }
    
}

/*
Two IP addresses are equal if all 4 octets of both addresses have identical
values. The function checks if two IP addresses are equal.
Inputs:
  ip1 - ipaddr_t input IP address 1
  ip2 - ipaddr_t input IP address 2
Return:
  1 - if ip1 and ip2 are equal
  0 - otherwise
*/
int is_equal(ipaddr_t ip1, ipaddr_t ip2)
{
        /*to check each octet*/
    if (ip1.octet1 == ip2.octet1 && ip1.octet2
    == ip2.octet2 && ip1.octet3 == ip2.octet3
    && ip1.octet4 == ip2.octet4) {
      return 1; /* ip1 is equal to ip2*/
    } else {

    return 0; /* ip1 is not equal to ip2 */
    }
}

/*
Two IP addresses are said to be in the same subnet if octet1, octet2 and octet3 
have identical values. The function checks if two ip addresses are in the same
subnet.
Note for students with a networking background: we are considering a simplified
definition of a subnet. Use the above definition given for this question.
Inputs:
  ip1 - ipaddr_t input IP address 1
  ip2 - ipaddr_t input IP address 2
Return:
  1 - if ip1 and ip2 are in the same subnet
  0 - otherwise
*/
int is_same_subnet(ipaddr_t ip1, ipaddr_t ip2)
{
    if (ip1.octet1 == ip2.octet1 && ip1.octet2 == 
    ip2.octet2 && ip1.octet3 == ip2.octet3){
      return 1; /* is the same subtnet*/
    }
    return 0; /* different subnet */
}

/*
The function prompts the user to enter IP addresses in the following format:
  octet1.octet2.octet3.octet4
in separate lines. If an input IP address is invalid, the function prints the
following error message:
  Invalid input
and prompt the user again to give a valid input. The function may scan up to 
addr_array_len valid IP addresses, or until the user enters -1.-1.-1.-1 as the
input, whichever occurs first.

Sample run 1 with addr_array_len=5, the function returns 2:
>192.168.1.1
>-192.168.1.1
Invalid input
>192.168.1.2
>-1.-1.-1.-1

Sample run 2 with addr_array_len=2, the function returns 2:
>192.168.1.1
>192.168.1.2

Inputs:
  addr_array_len - maximum possible number of inputs, this is the size of the
    addr_array array.
  addr_array - valid addresses from the user are saved to this array.
Return:
  the number of valid IP addresses given by the user
Post:
  After the function has been called, addr_array contains the valid IP
  addresses entered by the user.
*/
int get_valid_ipaddrs(ipaddr_t addr_array[], int addr_array_len)
{
    int count = 0; /*count of valid ip addresses*/
    ipaddr_t temp_ip;

    while (count < addr_array_len){
      printf(">");
      if (scanf("%d.%d.%d.%d", &temp_ip.octet1,
      &temp_ip.octet2, &temp_ip.octet3, &temp_ip.octet4)==4){

        /*check if user wants to quit*/
        if (temp_ip.octet1 == -1 && temp_ip.octet2 == -1 &&
        temp_ip.octet3 == -1 && temp_ip.octet4 == -1){
          break;
        }
        /*check if ip is valid*/
        if (is_valid(temp_ip)){
          addr_array[count] = temp_ip;
          count++;
        } else {
          printf("Invalid input\n");
        }
      } else {
        printf("Invalid input\n");
        /*clear input buffer?*/
      }
    }
    return count; /* MODIFY */
}

/*
Display IP addresses in the same subnet in addr_array. All addresses in the one
subnet should be displayed in the same line, in the same order the addresses
were entered. Each address is separated by one space, and each line has a
trailing space in the end of the line prior to the new line character.

Sample run 1 where addr_array contains the following IP addresses {192.168.1.1,
192.168.2.1, 192.168.1.2, 192.168.1.3} and addr_array_len=4:
192.168.1.1 192.168.1.2 192.168.1.3 
192.168.2.1 

Input:
  addr_array - contains IP addresses
  addr_array_len - the number of IP addresses in the addr_array
*/
void print_same_subnet(const ipaddr_t addr_array[], int addr_array_len)
{
  int checked[addr_array_len]; /*to track checked ips*/ 
  int i,j;
  /*initialise processed array*/
  for (i = 0; i < addr_array_len; i++){
    checked[i] = 0;
  }
  /*grouping ips by subnets*/
  for (i = 0; addr_array_len; i++){
    if (checked[i]) continue; /*skips if already checked*/
    print_ipaddr(addr_array[i]);
    printf(" ");
    checked[i] = 1;

    for (j = i; j < addr_array_len; j++){
      if (!checked[j] && is_same_subnet(addr_array[i]), addr_array[j]){
        print_ipaddr(addr_array[j]);
        printf(" ");
        processed[j] = 1;
      }
    }
    printf("\n");
  }
}
