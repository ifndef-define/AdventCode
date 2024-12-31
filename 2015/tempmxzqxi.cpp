std::cout << "Message block in hex:" << std::endl;
    for (size_t i = 0; i < msg.size(); ++i) {
        if (i > 0 && i % 8 == 0) {
        std::cout << std::endl;
        }
        if (i > 0 && i % 4 == 0) {
        std::cout << ' ';
        }
        std::cout << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(msg[i]);
    }
    std::cout << std::endl;
