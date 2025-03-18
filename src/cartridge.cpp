#include "cartridge.h"

#include <fstream>
#include <iostream>

#include "common.h"
#include "utils/file_util.h"

Cartridge::Cartridge(const char *filename)
    : m_filename(filename), m_romSize(0), m_romData(0), m_header(nullptr) {
    try {
        load();
        verifyChecksum();

        std::cout << "Cartridge loaded successfully\n";
        std::cout << std::format("{:<20}: ", "Cartridge title") << m_header->title << std::endl;
        std::cout << std::format("{:<20}: {:02x} ({})\n", "Cartridge type", m_header->cartridgeType, getCartridgeType());
        std::cout << std::format("{:<20}: {:02x} ({})\n", "Publisher", m_header->newLicenseeCode, getPublisher());
        std::cout << std::format("{:<20}: {} KB\n", "ROM size", (32 << m_header->romSize));
        std::cout << std::format("{:<20}: {:02x}\n", "RAM size", m_header->ramSize);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void Cartridge::load() {
    std::cout << "Loading cartridge" << m_filename << std::endl;

    m_romData = FileUtil::readFile(m_filename.c_str());

    m_header = reinterpret_cast<CartridgeHeader*>(m_romData.data() + 0x100);
    m_header->title[15] = '\0';
}

void Cartridge::verifyChecksum() const {
    uint8_t checksum = 0;
    for (uint16_t addr = 0x0134; addr <= 0x014C; addr++) {
        checksum = checksum - m_romData[addr] - 1;
    }

    if (checksum != m_header->headerChecksum) {
        throw std::runtime_error("Invalid header checksum");
    }
}

const char * Cartridge::getCartridgeType() const {
    if (m_header->cartridgeType <= 0x22) {
        return CARTRIDGE_TYPES[m_header->cartridgeType];
    }
    return "???";
}

const char * Cartridge::getPublisher() const {
    if (m_header->oldLicenseeCode != 0x33) {
        return OLD_PUBLISHERS[m_header->oldLicenseeCode];
    }
    if (m_header->newLicenseeCode <= 0xA4) {
        return NEW_PUBLISHERS[m_header->newLicenseeCode];
    }
    return "???";
}

const uint8_t Cartridge::read(uint16_t addr) const {
    return m_romData[addr];
}

void Cartridge::write(uint16_t addr, uint8_t data) {
    NO_IMPL
}