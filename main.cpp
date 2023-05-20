#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <vector>
#include <string>

class WtSimpleCrud : public Wt::WApplication
{
public:
    WtSimpleCrud(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *crudInputToAdd_;
    Wt::WLineEdit *crudInputToRemove_;
    Wt::WText *ackMsg;
    Wt::WText *listedEntries_;
    std::vector<Wt::WString> inputStorage_;
};

WtSimpleCrud::WtSimpleCrud(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("WtSimpleCrud");
    root()->addWidget(std::make_unique<Wt::WText>("Welcome to WtSimpleCrud"));
    root()->addWidget(std::make_unique<Wt::WBreak>());

    root()->addWidget(std::make_unique<Wt::WText>("Provide input to add "));
    crudInputToAdd_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *buttonAdd = root()->addWidget(std::make_unique<Wt::WPushButton>("Press to add"));

    root()->addWidget(std::make_unique<Wt::WBreak>());
    root()->addWidget(std::make_unique<Wt::WText>("Provide input to remove "));
    crudInputToRemove_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    Wt::WPushButton *buttonRemove = root()->addWidget(std::make_unique<Wt::WPushButton>("Press to remove"));

    root()->addWidget(std::make_unique<Wt::WBreak>());
    Wt::WPushButton *buttonList = root()->addWidget(std::make_unique<Wt::WPushButton>("List entries"));

    root()->addWidget(std::make_unique<Wt::WBreak>());
    ackMsg = root()->addWidget(std::make_unique<Wt::WText>());

    auto addAction = [this]{
        inputStorage_.push_back(crudInputToAdd_->text());
        ackMsg->setText("Added " + crudInputToAdd_->text() + " to storage");
    };
    buttonAdd->clicked().connect(addAction);

    auto removeAction = [this]{
        if (inputStorage_.empty())
        {
            ackMsg->setText("Storage is empty");
            return;
        }

        bool found = false;
        auto iter = inputStorage_.begin();
        for (; iter != inputStorage_.end(); ++iter)
        {
            if (*iter == crudInputToRemove_->text())
            {
                inputStorage_.erase(iter);
                found = true;
                break;
            }
        }
        if (found)
            ackMsg->setText("Removed " + crudInputToRemove_->text() + " from");
        else
            ackMsg->setText(crudInputToRemove_->text() + " not found in storage");
    };
    buttonRemove->clicked().connect(removeAction);

    auto listAction = [this]{
        Wt::WString tmpListedStorageString{};
        for (const auto& element : inputStorage_)
        {
            tmpListedStorageString += (element + ", ");
        }
        ackMsg->setText("Listed elements: " + tmpListedStorageString);
    };
    buttonList->clicked().connect(listAction);
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
      return std::make_unique<WtSimpleCrud>(env);
    });
}
