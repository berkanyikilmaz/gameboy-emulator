#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <string>
#include <vector>

class Bus;

struct CartridgeHeader {
    uint8_t entry[0x4];
    uint8_t nintendoLogo[0x30];
    char title[0x10];
    //uint8_t manufacturerCode[0x4];
    //uint8_t cgbFlag;
    uint16_t newLicenseeCode;
    uint8_t sgbFlag;
    uint8_t cartridgeType;
    uint8_t romSize;
    uint8_t ramSize;
    uint8_t destinationCode;
    uint8_t oldLicenseeCode;
    uint8_t maskRomVersion;
    uint8_t headerChecksum;
    uint16_t globalChecksum;
};

class Cartridge {
public:
    explicit Cartridge(const char* filename);

    void load();
    void verifyChecksum() const;

    std::string_view getCartridgeType() const;
    std::string_view getPublisher() const;

    const uint8_t read(uint16_t addr) const;
    void write(uint16_t addr, uint8_t data);

    void connectBus(Bus *bus);

    const std::string getFilename() const { return m_filename; }
    const uint32_t getRomSize() const { return m_romSize; }
    const std::vector<uint8_t>& getRomData() const { return m_romData; }
    const CartridgeHeader* getHeader() const { return m_header; }
private:
    std::string m_filename;
    uint32_t m_romSize;
    std::vector<uint8_t> m_romData;
    CartridgeHeader* m_header;

    Bus *m_bus;
};

#endif //CARTRIDGE_H
