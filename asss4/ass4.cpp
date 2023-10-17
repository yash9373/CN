#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// Function to convert a decimal IP address to binary
string decimalToBinaryIP(const string &decimalIP) {
    string binaryIP;
    size_t pos = 0;
    size_t found;

    for (int i = 0; i < 4; ++i) {
        found = decimalIP.find('.', pos);
        if (found == string::npos) {
            found = decimalIP.length();
        }

        int octet = stoi(decimalIP.substr(pos, found - pos));
        binaryIP += bitset<8>(octet).to_string();

        pos = found + 1;
    }

    return binaryIP;
}

// Function to calculate the number of subnets
int calculateSubnets(int subnetMask) {
    return 1 << (32 - subnetMask);
}

// Function to calculate the number of host addresses
int calculateHostAddresses(int subnetMask) {
    return (1 << (32 - subnetMask)) - 2;
}

// Function to calculate the last host address
string calculateLastHost(string ipAddress, int subnetMask) {
    // Convert the IP address to a 32-bit binary string
    string binaryIP = decimalToBinaryIP(ipAddress);

    // Calculate the number of host bits
    int hostBits = 32 - subnetMask;

    // Set the host bits to 1 to get the last host address
    for (int i = 31; i > 31 - hostBits; i--) {
        binaryIP[i] = '1';
    }

    return binaryIP;
}

int main() {
    string ipAddress;
    int subnetMask;

    // Input IP address and subnet mask
    cout << "Enter IP address (in decimal format, e.g., 10.0.0.10): ";
    cin >> ipAddress;

    cout << "Enter subnet mask (in CIDR notation, e.g., 24 for /24): ";
    cin >> subnetMask;

    // Calculate and display the subnet address
    cout << "Subnet Address (Binary): ";
    string binaryIP = decimalToBinaryIP(ipAddress);
    cout << binaryIP << " & ";

    string subnetMaskBinary(subnetMask, '1');
    subnetMaskBinary.resize(32, '0');
    cout << subnetMaskBinary << endl;

    // Calculate and display the number of subnets
    int subnets = calculateSubnets(subnetMask);
    cout << "Number of Subnets: " << subnets << endl;

    // Calculate and display the number of host addresses
    int hosts = calculateHostAddresses(subnetMask);
    cout << "Number of Host Addresses: " << hosts << endl;

    // Calculate and display the last host address
    string lastHost = calculateLastHost(ipAddress, subnetMask);
    cout << "Last Host Address (Binary): " << lastHost << endl;

    return 0;
}
