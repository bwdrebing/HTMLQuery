#include <gumbo.h>

class IGumboNodeVisitor {
    public:
        virtual ~IGumboNodeVisitor() = default;
        void iterate(GumboNode* node);
    protected:
        virtual void visit(GumboNode* node) = 0;
};

