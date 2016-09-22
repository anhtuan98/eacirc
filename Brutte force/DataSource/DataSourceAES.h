//
// Created by Dusan Klinec on 19.06.16.
//

#ifndef BRUTTE_FORCE_DATASOURCEAES_H
#define BRUTTE_FORCE_DATASOURCEAES_H

#include "DataSource.h"

class DataSourceAES : public DataSource {
public:
    DataSourceAES(unsigned long seed = 0, int Nr = 10);
    ~DataSourceAES() {}

    virtual long long getAvailableData() override;
    virtual void read(char *buffer, size_t size) override;
    virtual std::string desc() override;

private:
    uint8_t m_key[16];
    uint8_t m_iv[16];
private:
};


#endif //BRUTTE_FORCE_DATASOURCEAES_H