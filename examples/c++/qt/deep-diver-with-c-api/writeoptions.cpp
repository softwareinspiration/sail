/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2020 Dmitry Baryshev

    The MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include <QLabel>
#include <QSlider>

#include <sail/sail.h>

#include "writeoptions.h"
#include "ui_writeoptions.h"

class Q_DECL_HIDDEN WriteOptions::Private
{
public:
    QScopedPointer<Ui::WriteOptions> ui;
};

WriteOptions::WriteOptions(const QString &codecDescription, const sail_write_features *write_features, int input_pixel_format, QWidget *parent)
    : QDialog(parent)
    , d(new Private)
{
    d->ui.reset(new Ui::WriteOptions);
    d->ui->setupUi(this);

    d->ui->labelCodec->setText(codecDescription);

    init(write_features, input_pixel_format);
}

WriteOptions::~WriteOptions()
{
}

SailPixelFormat WriteOptions::pixelFormat() const
{
    return static_cast<SailPixelFormat>(d->ui->comboColor->currentData().toInt());
}

int WriteOptions::compressionLevel() const
{
    return d->ui->sliderCompression->isEnabled() ? d->ui->sliderCompression->value() : -1;
}

sail_status_t WriteOptions::init(const sail_write_features *write_features, int input_pixel_format)
{
    if (write_features->pixel_formats_mapping_node == nullptr) {
        disable();
        return SAIL_ERROR_UNSUPPORTED_PIXEL_FORMAT;
    }
    d->ui->labelColor->setText(tr("Output color:"));

    sail_pixel_formats_mapping_node *node = write_features->pixel_formats_mapping_node;
    bool allowedInputPixelFormat = false;

    while (node != nullptr) {
        if (node->input_pixel_format == input_pixel_format) {
            for (unsigned i = 0; i < node->output_pixel_formats_length; i++) {
                const char *output_pixel_format_str;

                SAIL_TRY(sail_pixel_format_to_string(node->output_pixel_formats[i], &output_pixel_format_str));

                d->ui->comboColor->addItem(output_pixel_format_str,
                                           /* user data */ node->output_pixel_formats[i]);
            }

            allowedInputPixelFormat = true;
            break;
        }

        node = node->next;
    }

    if (!allowedInputPixelFormat) {
        disable();
        return SAIL_ERROR_UNSUPPORTED_PIXEL_FORMAT;
    }

    /* Codecs support compression levels only when they support just a single compression. */
    if (write_features->compressions_length == 1) {
        d->ui->labelCompression->setText(tr("Compression:"));
        d->ui->sliderCompression->setMinimum(write_features->compression_level_min);
        d->ui->sliderCompression->setMaximum(write_features->compression_level_max);
        d->ui->sliderCompression->setValue(write_features->compression_level_default);
        d->ui->sliderCompression->setSingleStep(write_features->compression_level_step);
        d->ui->labelCompressionValue->setNum(d->ui->sliderCompression->value());

        connect(d->ui->sliderCompression, &QSlider::valueChanged, [&](int value) {
            d->ui->labelCompressionValue->setNum(value);
        });
    } else {
        d->ui->labelCompression->setText(tr("Compression levels are not available"));
        d->ui->labelCompression->setEnabled(false);
        d->ui->sliderCompression->setEnabled(false);
    }

    return SAIL_OK;
}

void WriteOptions::disable()
{
    d->ui->labelColor->setText(tr("Output color selection is not available"));
    d->ui->labelColor->setEnabled(false);
    d->ui->comboColor->setEnabled(false);
}
