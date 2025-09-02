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
    /*to check each octect*/
    int i, j, k;
    int ipLength = sizeof(ip); /*to have a length of the structure*/
    printf("ipLength: %d\n", ipLength);
    int checkedCount = 0; /*to initialise a checked counter*/
    int checkedOctet[4]; /*to initialise a checked octet*/

    for (i = 0; i < ipLength; i++){
      int currentOctet = ip[i];
      int alreadyChecked = 0;
      /*to count if already checked*/
      for (j =0; j < checkedCount; j++){
        if (checkedOctet[j] == currentOctet){
          alreadyChecked = 1;
          break;
        }
      }
      if (alreadyChecked) continue;
      /*we can check if it falls in the range 0 to 255*/
      int countOctet;
      for (k = 0; k < ipLength; k++){
        if (checkedOctet[k] >= 0 && checkedOctet[k] <= 255){
          countOctet++;
        
        /*marked octet as checked*/
        checkedOctet[checkedCount++] = currentOctet;
      }
      
    }
    return 0; /* MODIFY */
    else {
      printf("Input is invalid\n");
      return 1;
    }
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
        /*to check each octect*/
    int i, j, k;
    int ipLength = sizeof(ip); /*to have a length of the structure*/
    printf("ipLength: %d\n", ipLength);
    int checkedCount = 0; /*to initialise a checked counter*/
    int checkedOctet[4]; /*to initialise a checked octet*/

    for (i = 0; i < ipLength; i++){
      int currentOctet = ip[i];
      int alreadyChecked = 0;
      /*to count if already checked*/
      for (j =0; j < checkedCount; j++){
        if (checkedOctet[j] == currentOctet){
          alreadyChecked = 1;
          break;
        }
      }
      if (alreadyChecked) continue;
      /*we can check if it falls in the range 0 to 255*/
      int countOctet;
      for (k = 0; k < ipLength; k++){
        if (checkedOctet[k] == currentOctet){
          countOctet++;
        
        /*marked octet as checked*/
        checkedOctet[checkedCount++] = currentOctet;
      }
      
    }
    if (countOctet == 4){
      printf("ip1 and ip2 are equal\n", ip);
      return 1;
    } else
    //
    }


    return 0; /* MODIFY */
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
    return 0; /* MODIFY */
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
    return 0; /* MODIFY */
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

}
