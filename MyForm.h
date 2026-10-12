#pragma once
#include "Image_Class.h"
#include "Filters.h"
#include "ImageHistory.h"
#include <msclr/marshal_cppstd.h>

namespace BabyPhotoshop {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;
    using namespace System::Runtime::InteropServices;

    // Helper class to show input dialog boxes
    public ref class Prompt
    {
    public:
        static String^ ShowDialog(String^ text, String^ caption)
        {
            Form^ prompt = gcnew Form();
            prompt->Width = 320;
            prompt->Height = 160;
            prompt->FormBorderStyle = FormBorderStyle::FixedDialog;
            prompt->Text = caption;
            prompt->StartPosition = FormStartPosition::CenterScreen;
            prompt->MaximizeBox = false;
            prompt->MinimizeBox = false;

            Label^ textLabel = gcnew Label();
            textLabel->Left = 20;
            textLabel->Top = 20;
            textLabel->Width = 260;
            textLabel->Text = text;

            TextBox^ textBox = gcnew TextBox();
            textBox->Left = 20;
            textBox->Top = 50;
            textBox->Width = 260;

            Button^ confirmation = gcnew Button();
            confirmation->Text = L"OK";
            confirmation->Left = 180;
            confirmation->Top = 85;
            confirmation->Width = 100;
            confirmation->DialogResult = System::Windows::Forms::DialogResult::OK;

            prompt->Controls->Add(textLabel);
            prompt->Controls->Add(textBox);
            prompt->Controls->Add(confirmation);
            prompt->AcceptButton = confirmation;

            return prompt->ShowDialog() == System::Windows::Forms::DialogResult::OK ? textBox->Text : L"";
        }

        // Helper that shows a choice dialog (e.g., flip direction, blur level)
        static int ShowChoice(String^ text, String^ caption, cli::array<String^>^ options)
        {
            Form^ prompt = gcnew Form();
            prompt->Width = 320;
            prompt->Height = 60 + options->Length * 40 + 20;
            prompt->FormBorderStyle = FormBorderStyle::FixedDialog;
            prompt->Text = caption;
            prompt->StartPosition = FormStartPosition::CenterScreen;
            prompt->MaximizeBox = false;
            prompt->MinimizeBox = false;

            Label^ textLabel = gcnew Label();
            textLabel->Left = 20;
            textLabel->Top = 10;
            textLabel->Width = 260;
            textLabel->Text = text;
            prompt->Controls->Add(textLabel);

            for (int i = 0; i < options->Length; i++) {
                Button^ btn = gcnew Button();
                btn->Text = options[i];
                btn->Left = 20;
                btn->Top = 40 + i * 40;
                btn->Width = 260;
                btn->Height = 35;
                btn->Tag = i;
                btn->DialogResult = System::Windows::Forms::DialogResult::OK;
                prompt->Controls->Add(btn);
            }

            prompt->ShowDialog();
            return -1;
        }
    };

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            currentImage = new ::Image();
            history = nullptr;
            UpdateHistoryButtons();
        }

    protected:
        ~MyForm()
        {
            if (components) delete components;
            if (currentImage) delete currentImage;
            if (history) {
                delete history;
                history = nullptr;
            }
        }

    private:
        ::Image* currentImage;
        ImageHistory* history;

        // UI Elements
        System::Windows::Forms::PictureBox^ pictureBox1;
        System::Windows::Forms::Button^ btnLoad;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnBackward;
        System::Windows::Forms::Button^ btnForward;
        System::Windows::Forms::FlowLayoutPanel^ filterPanel;
        System::Windows::Forms::Panel^ mainPanel;

        // All 18 filter buttons
        System::Windows::Forms::Button^ btn1;
        System::Windows::Forms::Button^ btn2;
        System::Windows::Forms::Button^ btn3;
        System::Windows::Forms::Button^ btn4;
        System::Windows::Forms::Button^ btn5;
        System::Windows::Forms::Button^ btn6;
        System::Windows::Forms::Button^ btn7;
        System::Windows::Forms::Button^ btn8;
        System::Windows::Forms::Button^ btn9;
        System::Windows::Forms::Button^ btn10;
        System::Windows::Forms::Button^ btn11;
        System::Windows::Forms::Button^ btn12;
        System::Windows::Forms::Button^ btn13;
        System::Windows::Forms::Button^ btn14;
        System::Windows::Forms::Button^ btn15;
        System::Windows::Forms::Button^ btn16;
        System::Windows::Forms::Button^ btn17;
        System::Windows::Forms::Button^ btn18;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
            this->btnLoad = (gcnew System::Windows::Forms::Button());
            this->btnSave = (gcnew System::Windows::Forms::Button());
            this->btnBackward = (gcnew System::Windows::Forms::Button());
            this->btnForward = (gcnew System::Windows::Forms::Button());
            this->filterPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
            this->mainPanel = (gcnew System::Windows::Forms::Panel());

            this->btn1 = (gcnew System::Windows::Forms::Button());
            this->btn2 = (gcnew System::Windows::Forms::Button());
            this->btn3 = (gcnew System::Windows::Forms::Button());
            this->btn4 = (gcnew System::Windows::Forms::Button());
            this->btn5 = (gcnew System::Windows::Forms::Button());
            this->btn6 = (gcnew System::Windows::Forms::Button());
            this->btn7 = (gcnew System::Windows::Forms::Button());
            this->btn8 = (gcnew System::Windows::Forms::Button());
            this->btn9 = (gcnew System::Windows::Forms::Button());
            this->btn10 = (gcnew System::Windows::Forms::Button());
            this->btn11 = (gcnew System::Windows::Forms::Button());
            this->btn12 = (gcnew System::Windows::Forms::Button());
            this->btn13 = (gcnew System::Windows::Forms::Button());
            this->btn14 = (gcnew System::Windows::Forms::Button());
            this->btn15 = (gcnew System::Windows::Forms::Button());
            this->btn16 = (gcnew System::Windows::Forms::Button());
            this->btn17 = (gcnew System::Windows::Forms::Button());
            this->btn18 = (gcnew System::Windows::Forms::Button());

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
            this->filterPanel->SuspendLayout();
            this->SuspendLayout();

            //
            // pictureBox1
            //
            this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
            this->pictureBox1->Location = System::Drawing::Point(270, 10);
            this->pictureBox1->Name = L"pictureBox1";
            this->pictureBox1->Size = System::Drawing::Size(760, 540);
            this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->pictureBox1->TabIndex = 0;
            this->pictureBox1->TabStop = false;
            this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right);
            //
            // btnLoad
            //
            this->btnLoad->BackColor = System::Drawing::Color::FromArgb(0, 122, 204);
            this->btnLoad->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLoad->ForeColor = System::Drawing::Color::White;
            this->btnLoad->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
            this->btnLoad->Location = System::Drawing::Point(280, 560);
            this->btnLoad->Name = L"btnLoad";
            this->btnLoad->Size = System::Drawing::Size(120, 40);
            this->btnLoad->TabIndex = 1;
            this->btnLoad->Text = L"Load Image";
            this->btnLoad->UseVisualStyleBackColor = false;
            this->btnLoad->Click += gcnew System::EventHandler(this, &MyForm::btnLoad_Click);
            this->btnLoad->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // btnSave
            //
            this->btnSave->BackColor = System::Drawing::Color::FromArgb(30, 130, 76);
            this->btnSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnSave->ForeColor = System::Drawing::Color::White;
            this->btnSave->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
            this->btnSave->Location = System::Drawing::Point(415, 560);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(120, 40);
            this->btnSave->TabIndex = 2;
            this->btnSave->Text = L"Save Image";
            this->btnSave->UseVisualStyleBackColor = false;
            this->btnSave->Click += gcnew System::EventHandler(this, &MyForm::btnSave_Click);
            this->btnSave->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // btnBackward
            //
            this->btnBackward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
            this->btnBackward->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnBackward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
            this->btnBackward->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnBackward->Location = System::Drawing::Point(550, 560);
            this->btnBackward->Name = L"btnBackward";
            this->btnBackward->Size = System::Drawing::Size(140, 40);
            this->btnBackward->TabIndex = 4;
            this->btnBackward->Text = L"<- Backward";
            this->btnBackward->UseVisualStyleBackColor = false;
            this->btnBackward->Enabled = false;
            this->btnBackward->Click += gcnew System::EventHandler(this, &MyForm::btnBackward_Click);
            this->btnBackward->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // btnForward
            //
            this->btnForward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
            this->btnForward->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnForward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
            this->btnForward->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->btnForward->Location = System::Drawing::Point(705, 560);
            this->btnForward->Name = L"btnForward";
            this->btnForward->Size = System::Drawing::Size(140, 40);
            this->btnForward->TabIndex = 5;
            this->btnForward->Text = L"Forward ->";
            this->btnForward->UseVisualStyleBackColor = false;
            this->btnForward->Enabled = false;
            this->btnForward->Click += gcnew System::EventHandler(this, &MyForm::btnForward_Click);
            this->btnForward->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
            //
            // filterPanel
            //
            this->filterPanel->AutoScroll = true;
            this->filterPanel->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
            this->filterPanel->WrapContents = false;
            this->filterPanel->Location = System::Drawing::Point(5, 10);
            this->filterPanel->Name = L"filterPanel";
            this->filterPanel->Size = System::Drawing::Size(255, 590);
            this->filterPanel->TabIndex = 3;
            this->filterPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);

            // Create all 18 buttons with names
            cli::array<String^>^ names = gcnew cli::array<String^> {
                L"1. Grayscale", L"2. Black & White", L"3. Invert",
                L"4. Add Frame", L"5. Flip", L"6. Rotate",
                L"7. Darken/Lighten", L"8. Resize", L"9. Merge",
                L"10. Edge Detect", L"11. Crop", L"12. Blur",
                L"13. Sunlight", L"14. TV Effect", L"15. Purple",
                L"16. Infrared", L"17. Skew", L"18. Oil Paint"
            };

            cli::array<Button^>^ btns = gcnew cli::array<Button^> {
                btn1, btn2, btn3, btn4, btn5, btn6,
                btn7, btn8, btn9, btn10, btn11, btn12,
                btn13, btn14, btn15, btn16, btn17, btn18
            };

            cli::array<System::EventHandler^>^ handlers = gcnew cli::array<System::EventHandler^> {
                gcnew System::EventHandler(this, &MyForm::btn1_Click),
                gcnew System::EventHandler(this, &MyForm::btn2_Click),
                gcnew System::EventHandler(this, &MyForm::btn3_Click),
                gcnew System::EventHandler(this, &MyForm::btn4_Click),
                gcnew System::EventHandler(this, &MyForm::btn5_Click),
                gcnew System::EventHandler(this, &MyForm::btn6_Click),
                gcnew System::EventHandler(this, &MyForm::btn7_Click),
                gcnew System::EventHandler(this, &MyForm::btn8_Click),
                gcnew System::EventHandler(this, &MyForm::btn9_Click),
                gcnew System::EventHandler(this, &MyForm::btn10_Click),
                gcnew System::EventHandler(this, &MyForm::btn11_Click),
                gcnew System::EventHandler(this, &MyForm::btn12_Click),
                gcnew System::EventHandler(this, &MyForm::btn13_Click),
                gcnew System::EventHandler(this, &MyForm::btn14_Click),
                gcnew System::EventHandler(this, &MyForm::btn15_Click),
                gcnew System::EventHandler(this, &MyForm::btn16_Click),
                gcnew System::EventHandler(this, &MyForm::btn17_Click),
                gcnew System::EventHandler(this, &MyForm::btn18_Click)
            };

            for (int i = 0; i < 18; i++) {
                btns[i]->Size = System::Drawing::Size(240, 45);
                btns[i]->Text = names[i];
                btns[i]->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
                btns[i]->BackColor = System::Drawing::Color::FromArgb(60, 60, 65);
                btns[i]->ForeColor = System::Drawing::Color::White;
                btns[i]->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
                btns[i]->TextAlign = ContentAlignment::MiddleLeft;
                btns[i]->Margin = System::Windows::Forms::Padding(3);
                btns[i]->Click += handlers[i];
                this->filterPanel->Controls->Add(btns[i]);
            }

            //
            // MyForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->ClientSize = System::Drawing::Size(1000, 610);
            this->Controls->Add(this->filterPanel);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnLoad);
            this->Controls->Add(this->btnBackward);
            this->Controls->Add(this->btnForward);
            this->Controls->Add(this->pictureBox1);
            this->Name = L"MyForm";
            this->Text = L"Baby Photoshop - FCAI";
            this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
            this->MinimumSize = System::Drawing::Size(1000, 650);
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
            this->filterPanel->ResumeLayout(false);
            this->ResumeLayout(false);
        }
#pragma endregion

    private:
        // =============================================
        // THE BRIDGE: C++ pixels -> .NET Bitmap
        // =============================================
        void UpdatePictureBox() {
            if (currentImage->width <= 0 || currentImage->height <= 0) return;

            int w = currentImage->width;
            int h = currentImage->height;

            Bitmap^ bmp = gcnew Bitmap(w, h, PixelFormat::Format24bppRgb);
            System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, w, h);
            BitmapData^ bmpData = bmp->LockBits(rect, ImageLockMode::WriteOnly, bmp->PixelFormat);

            IntPtr ptr = bmpData->Scan0;
            int bytes = Math::Abs(bmpData->Stride) * h;
            cli::array<Byte>^ rgbValues = gcnew cli::array<Byte>(bytes);

            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int stbi_index = (y * w + x) * currentImage->channels;
                    int bmp_index = y * bmpData->Stride + x * 3;

                    // Bitmap expects BGR
                    rgbValues[bmp_index + 2] = currentImage->imageData[stbi_index + 0]; // R
                    rgbValues[bmp_index + 1] = currentImage->imageData[stbi_index + 1]; // G
                    rgbValues[bmp_index + 0] = currentImage->imageData[stbi_index + 2]; // B
                }
            }

            Marshal::Copy(rgbValues, 0, ptr, bytes);
            bmp->UnlockBits(bmpData);
            pictureBox1->Image = bmp;
        }

        // =============================================
        // UNDO / REDO HISTORY SUPPORT
        // =============================================
        void UpdateHistoryButtons() {
            if (history == nullptr) {
                btnBackward->Enabled = false;
                btnForward->Enabled = false;
                btnBackward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnForward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnBackward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
                btnForward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
                return;
            }

            bool canBack = history->canBackward();
            bool canFwd = history->canForward();

            btnBackward->Enabled = canBack;
            btnForward->Enabled = canFwd;

            if (canBack) {
                btnBackward->BackColor = System::Drawing::Color::FromArgb(90, 65, 140);
                btnBackward->ForeColor = System::Drawing::Color::White;
            } else {
                btnBackward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnBackward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
            }

            if (canFwd) {
                btnForward->BackColor = System::Drawing::Color::FromArgb(90, 65, 140);
                btnForward->ForeColor = System::Drawing::Color::White;
            } else {
                btnForward->BackColor = System::Drawing::Color::FromArgb(45, 45, 48);
                btnForward->ForeColor = System::Drawing::Color::FromArgb(100, 100, 100);
            }
        }

        void RecordHistory(String^ actionName) {
            if (history != nullptr && currentImage != nullptr && currentImage->imageData != nullptr) {
                std::string name = msclr::interop::marshal_as<std::string>(actionName);
                history->newImage(*currentImage, name);
                UpdateHistoryButtons();
            }
        }

        System::Void btnBackward_Click(System::Object^ sender, System::EventArgs^ e) {
            if (history != nullptr && history->canBackward()) {
                Node prevNode = history->backward(1);
                *currentImage = prevNode.image;
                UpdatePictureBox();
                UpdateHistoryButtons();
            }
        }

        System::Void btnForward_Click(System::Object^ sender, System::EventArgs^ e) {
            if (history != nullptr && history->canForward()) {
                Node nextNode = history->forward(1);
                *currentImage = nextNode.image;
                UpdatePictureBox();
                UpdateHistoryButtons();
            }
        }

        // Helper: check if image is loaded
        bool CheckImageLoaded() {
            if (currentImage->imageData == nullptr || currentImage->width <= 0) {
                MessageBox::Show("Please load an image first!", "No Image", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return false;
            }
            return true;
        }

        // =============================================
        // LOAD & SAVE & EXIT HANDLERS
        // =============================================
        bool PromptAndSaveImage() {
            if (!CheckImageLoaded()) return false;
            SaveFileDialog^ sfd = gcnew SaveFileDialog();
            sfd->Filter = "JPG Image|*.jpg|PNG Image|*.png|BMP Image|*.bmp|TGA Image|*.tga";
            if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                std::string filepath = msclr::interop::marshal_as<std::string>(sfd->FileName);
                try {
                    currentImage->saveImage(filepath);
                    MessageBox::Show("Image saved successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    return true;
                } catch (...) {
                    MessageBox::Show("Failed to save image.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return false;
                }
            }
            return false;
        }

        System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
            if (currentImage != nullptr && currentImage->imageData != nullptr && currentImage->width > 0) {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    "Would you like to save the current image before exiting?",
                    "Save before Exit",
                    MessageBoxButtons::YesNoCancel,
                    MessageBoxIcon::Question);

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    bool saved = PromptAndSaveImage();
                    if (!saved) {
                        e->Cancel = true; // User cancelled save file dialog, stay in app
                    }
                }
                else if (result == System::Windows::Forms::DialogResult::Cancel) {
                    e->Cancel = true; // User aborted exit
                }
            }
        }

        System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
            if (currentImage != nullptr && currentImage->imageData != nullptr && currentImage->width > 0) {
                System::Windows::Forms::DialogResult res = MessageBox::Show(
                    "Would you like to save the current image before loading a new one?",
                    "Save Current Image",
                    MessageBoxButtons::YesNoCancel,
                    MessageBoxIcon::Question);

                if (res == System::Windows::Forms::DialogResult::Yes) {
                    bool saved = PromptAndSaveImage();
                    if (!saved) return;
                }
                else if (res == System::Windows::Forms::DialogResult::Cancel) {
                    return;
                }
            }

            OpenFileDialog^ ofd = gcnew OpenFileDialog();
            ofd->Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp;*.tga";
            if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                std::string filepath = msclr::interop::marshal_as<std::string>(ofd->FileName);
                try {
                    currentImage->loadNewImage(filepath);
                    if (history != nullptr) {
                        delete history;
                        history = nullptr;
                    }
                    history = new ImageHistory(*currentImage, filepath);
                    UpdatePictureBox();
                    UpdateHistoryButtons();
                } catch (...) {
                    MessageBox::Show("Failed to load image!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
            PromptAndSaveImage();
        }

        // =============================================
        // FILTER 1: Grayscale (no params)
        // =============================================
        System::Void btn1_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyGrayscale(*currentImage);
            RecordHistory(L"Grayscale");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 2: Black & White (no params)
        // =============================================
        System::Void btn2_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyBlackAndWhite(*currentImage);
            RecordHistory(L"Black & White");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 3: Invert (no params)
        // =============================================
        System::Void btn3_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyInvert(*currentImage);
            RecordHistory(L"Invert");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 4: Add Frame (submenu: simple/decorated)
        // =============================================
        System::Void btn4_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "Click YES for Simple Frame, NO for Decorated Frame",
                "Add Frame", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
            if (result == System::Windows::Forms::DialogResult::Yes) {
                applyFrame(*currentImage, 1);
                RecordHistory(L"Simple Frame");
                UpdatePictureBox();
            } else if (result == System::Windows::Forms::DialogResult::No) {
                applyFrame(*currentImage, 2);
                RecordHistory(L"Decorated Frame");
                UpdatePictureBox();
            }
        }

        // =============================================
        // FILTER 5: Flip (submenu: horizontal/vertical)
        // =============================================
        System::Void btn5_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "Click YES for Horizontal Flip, NO for Vertical Flip",
                "Flip Image", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
            if (result == System::Windows::Forms::DialogResult::Yes) {
                applyFlipHorizontal(*currentImage);
                RecordHistory(L"Horizontal Flip");
                UpdatePictureBox();
            } else if (result == System::Windows::Forms::DialogResult::No) {
                applyFlipVertical(*currentImage);
                RecordHistory(L"Vertical Flip");
                UpdatePictureBox();
            }
        }

        // =============================================
        // FILTER 6: Rotate (text box: 90, 180, 270)
        // =============================================
        System::Void btn6_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ angleStr = Prompt::ShowDialog("Enter rotation angle (90, 180, or 270):", "Rotate Image");
            if (String::IsNullOrEmpty(angleStr)) return;
            try {
                int angle = Int32::Parse(angleStr);
                if (angle == 90 || angle == 180 || angle == 270) {
                    ::Image result = applyRotate(*currentImage, angle);
                    *currentImage = result;
                    RecordHistory(L"Rotate");
                    UpdatePictureBox();
                } else {
                    MessageBox::Show("Please enter 90, 180, or 270.", "Invalid Angle", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                }
            } catch (...) {
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 7: Darken/Lighten (submenu + text box for %)
        // =============================================
        System::Void btn7_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "Click YES to Darken, NO to Lighten",
                "Darken / Lighten", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Cancel) return;

            String^ pctStr = Prompt::ShowDialog("Enter percentage (0-100):", "Brightness %");
            if (String::IsNullOrEmpty(pctStr)) return;
            try {
                int pct = Int32::Parse(pctStr);
                if (pct < 0 || pct > 100) {
                    MessageBox::Show("Percentage must be between 0 and 100.", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                if (result == System::Windows::Forms::DialogResult::Yes) {
                    applyDarken(*currentImage, pct);
                    RecordHistory(L"Darken");
                } else {
                    applyLighten(*currentImage, pct);
                    RecordHistory(L"Lighten");
                }
                UpdatePictureBox();
            } catch (...) {
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 8: Resize (text boxes for width & height)
        // =============================================
        System::Void btn8_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ wStr = Prompt::ShowDialog("Enter new width:", "Resize Image");
            if (String::IsNullOrEmpty(wStr)) return;
            String^ hStr = Prompt::ShowDialog("Enter new height:", "Resize Image");
            if (String::IsNullOrEmpty(hStr)) return;
            try {
                int newW = Int32::Parse(wStr);
                int newH = Int32::Parse(hStr);
                if (newW <= 0 || newH <= 0) {
                    MessageBox::Show("Dimensions must be positive.", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                ::Image result = applyResize(*currentImage, newW, newH);
                *currentImage = result;
                RecordHistory(L"Resize");
                UpdatePictureBox();
            } catch (...) {
                MessageBox::Show("Please enter valid numbers.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 9: Merge (file picker + submenu)
        // =============================================
        System::Void btn9_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;

            // Pick second image
            OpenFileDialog^ ofd = gcnew OpenFileDialog();
            ofd->Title = "Select the second image to merge with";
            ofd->Filter = "Image Files|*.jpg;*.jpeg;*.png;*.bmp;*.tga";
            if (ofd->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            std::string filepath = msclr::interop::marshal_as<std::string>(ofd->FileName);
            ::Image img2;
            try {
                img2.loadNewImage(filepath);
            } catch (...) {
                MessageBox::Show("Failed to load second image!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            System::Windows::Forms::DialogResult result = MessageBox::Show(
                "YES = Resize both to biggest dimensions & merge\nNO = Merge common area only (crop)",
                "Merge Mode", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);

            if (result == System::Windows::Forms::DialogResult::Cancel) return;

            int mode = (result == System::Windows::Forms::DialogResult::Yes) ? 1 : 2;
            ::Image merged = applyMerge(*currentImage, img2, mode);
            *currentImage = merged;
            RecordHistory(L"Merge");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 10: Edge Detect (no params)
        // =============================================
        System::Void btn10_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyEdgeDetect(*currentImage);
            RecordHistory(L"Edge Detect");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 11: Crop (text boxes for x, y, w, h)
        // =============================================
        System::Void btn11_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ xStr = Prompt::ShowDialog("Start X coordinate:", "Crop Image");
            if (String::IsNullOrEmpty(xStr)) return;
            String^ yStr = Prompt::ShowDialog("Start Y coordinate:", "Crop Image");
            if (String::IsNullOrEmpty(yStr)) return;
            String^ wStr = Prompt::ShowDialog("Crop width:", "Crop Image");
            if (String::IsNullOrEmpty(wStr)) return;
            String^ hStr = Prompt::ShowDialog("Crop height:", "Crop Image");
            if (String::IsNullOrEmpty(hStr)) return;
            try {
                int sx = Int32::Parse(xStr);
                int sy = Int32::Parse(yStr);
                int cw = Int32::Parse(wStr);
                int ch = Int32::Parse(hStr);
                if (sx < 0 || sy < 0 || cw <= 0 || ch <= 0 ||
                    sx + cw > currentImage->width || sy + ch > currentImage->height) {
                    MessageBox::Show("Crop area is out of bounds!", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                ::Image result = applyCrop(*currentImage, sx, sy, cw, ch);
                *currentImage = result;
                RecordHistory(L"Crop");
                UpdatePictureBox();
            } catch (...) {
                MessageBox::Show("Please enter valid numbers.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 12: Blur (submenu: light/medium/strong)
        // =============================================
        System::Void btn12_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ levelStr = Prompt::ShowDialog("Enter blur level (1=Light, 2=Medium, 3=Strong):", "Blur Image");
            if (String::IsNullOrEmpty(levelStr)) return;
            try {
                int level = Int32::Parse(levelStr);
                if (level < 1 || level > 3) {
                    MessageBox::Show("Please enter 1, 2, or 3.", "Invalid", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }
                this->Cursor = Cursors::WaitCursor;
                applyBlur(*currentImage, level);
                this->Cursor = Cursors::Default;
                RecordHistory(L"Blur");
                UpdatePictureBox();
            } catch (...) {
                this->Cursor = Cursors::Default;
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 13: Sunlight (no params)
        // =============================================
        System::Void btn13_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applySunlight(*currentImage);
            RecordHistory(L"Sunlight");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 14: TV / Den Den Mushi (no params)
        // =============================================
        System::Void btn14_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyTV(*currentImage);
            RecordHistory(L"TV Effect");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 15: Purple (no params)
        // =============================================
        System::Void btn15_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyPurple(*currentImage);
            RecordHistory(L"Purple");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 16: Infrared (no params)
        // =============================================
        System::Void btn16_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            applyInfrared(*currentImage);
            RecordHistory(L"Infrared");
            UpdatePictureBox();
        }

        // =============================================
        // FILTER 17: Skew (text box for angle)
        // =============================================
        System::Void btn17_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            String^ angleStr = Prompt::ShowDialog("Enter skew angle in degrees (e.g. 20 to 45):", "Skew Image");
            if (String::IsNullOrEmpty(angleStr)) return;
            try {
                double angle = Double::Parse(angleStr);
                this->Cursor = Cursors::WaitCursor;
                ::Image result = applySkew(*currentImage, angle);
                *currentImage = result;
                this->Cursor = Cursors::Default;
                RecordHistory(L"Skew");
                UpdatePictureBox();
            } catch (...) {
                this->Cursor = Cursors::Default;
                MessageBox::Show("Please enter a valid number.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // =============================================
        // FILTER 18: Oil Paint (no params, slow)
        // =============================================
        System::Void btn18_Click(System::Object^ sender, System::EventArgs^ e) {
            if (!CheckImageLoaded()) return;
            this->Cursor = Cursors::WaitCursor;
            applyOilPaint(*currentImage);
            this->Cursor = Cursors::Default;
            RecordHistory(L"Oil Paint");
            UpdatePictureBox();
        }
    };
}
