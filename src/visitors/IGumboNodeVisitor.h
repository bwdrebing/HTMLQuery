#include <gumbo.h>

class IGumboNodeVisitor {
    public:
        void iterate(GumboNode* node);
    protected:
        virtual void visit(GumboNode* node) = 0;
};

