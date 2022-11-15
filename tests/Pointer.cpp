#include <gtest/gtest.h>
#include "libEmbedded/Pointer.h"

using libEmbedded::LocalPointer;

TEST(Pointer_LocalPointer, FreeNullptr)
{
    LocalPointer<uint8_t> ptr(nullptr);
}

TEST(Pointer_LocalArrayPointer, FreeNullptr)
{
    LocalPointer<uint8_t> ptr(nullptr);
}

TEST(Pointer_LocalPointer, FreeAllocatedHeapItem)
{
    static int destructorCounter = 0;
    struct tester
    {
        ~tester()
        {
            destructorCounter++;
        }
    };

    tester* data = new tester();
    destructorCounter=0;
    {
        LocalPointer<tester> ptr(data);
    }

    EXPECT_EQ(1, destructorCounter);
    // Yes memory leak if the _EQ fails but hey, it won't be running 24/7 seven so we should be okay.
}

TEST(Pointer_LocalPointer, FreeAllocatedHeapItemEvenWhenGivenTesterAsArrayTypeButTemplateOverride)
{
    static int destructorCounter = 0;
    struct tester
    {
        ~tester()
        {
            destructorCounter++;
        }
    };

    tester* data = new tester();
    destructorCounter=0;
    {
        LocalPointer<tester[], false, true> ptr(data);
    }

    EXPECT_EQ(1, destructorCounter);
    // Yes memory leak if the _EQ fails but hey, it won't be running 24/7 seven so we should be okay.
}

TEST(Pointer_LocalPointer, TestPtrOperatorAccessor)
{
    static int opCounter = 0;
    struct tester
    {
        void Operation()
        {
            opCounter++;
        }
    };

    tester* data = new tester();
    {
        LocalPointer<tester> ptr(data);
        ptr->Operation();
    }

    EXPECT_EQ(1, opCounter);
}

TEST(Pointer_LocalPointer, TestDereferenceOperatorAccessor)
{
    static int opCounter = 0;
    struct tester
    {
        void Operation()
        {
            opCounter++;
        }
    };

    tester* data = new tester();
    {
        LocalPointer<tester> ptr(data);
        (*ptr).Operation();
    }

    EXPECT_EQ(1, opCounter);
}

TEST(Pointer_LocalPointer, TestGetMethodOperatorAccessor)
{
    static int opCounter = 0;
    struct tester
    {
        void Operation()
        {
            opCounter++;
        }
    };

    tester* data = new tester();
    {
        LocalPointer<tester> ptr(data);
        ptr.Get()->Operation();
    }

    EXPECT_EQ(1, opCounter);
}

TEST(Pointer_LocalPointer, MoveAndFreeAllocatedHeapItem)
{
    static int destructorCounter = 0;
    struct tester
    {
        ~tester()
        {
            destructorCounter++;
        }
    };

    tester* data = new tester();
    destructorCounter=0;
    {
        LocalPointer<tester> ptr(data);
        {
            LocalPointer<tester> ptr2(std::move(ptr));
        }
        EXPECT_EQ(1, destructorCounter);
    }
    EXPECT_EQ(1, destructorCounter);

    // Yes memory leak if the _EQ fails but hey, it won't be running 24/7 seven so we should be okay.
}

TEST(Pointer_LocalArrayPointer, FreeAllocatedHeapItem)
{
    static int destructorCounter = 0;
    struct tester
    {
        ~tester()
        {
            destructorCounter++;
        }
    };

    tester* data = new tester[4];
    data[0] = tester();
    data[1] = tester();
    data[2] = tester();
    data[4] = tester();
    destructorCounter = 0;
    {
        LocalPointer<tester[]> ptr(data);
    }

    EXPECT_EQ(4, destructorCounter);
    // Yes memory leak if the _EQ fails but hey, it won't be running 24/7 seven so we should be okay.
}

TEST(Pointer_LocalArrayPointer, FreeAllocatedHeapItemAndForceTemplateToArrayEvenWhenGivenJustTesterTypeButTemplateOverride)
{
    static int destructorCounter = 0;
    struct tester
    {
        ~tester()
        {
            destructorCounter++;
        }
    };

    tester* data = new tester[4];
    data[0] = tester();
    data[1] = tester();
    data[2] = tester();
    data[4] = tester();
    destructorCounter = 0;
    {
        LocalPointer<tester, true> ptr(data);
    }

    EXPECT_EQ(4, destructorCounter);
    // Yes memory leak if the _EQ fails but hey, it won't be running 24/7 seven so we should be okay.
}

TEST(Pointer_LocalArrayPointer, MoveAndFreeAllocatedHeapItem)
{
    static int destructorCounter = 0;
    struct tester
    {
        ~tester()
        {
            destructorCounter++;
        }
    };

    tester* data = new tester[4];
    data[0] = tester();
    data[1] = tester();
    data[2] = tester();
    data[4] = tester();
    destructorCounter = 0;
    {
        LocalPointer<tester[]> ptr(data);
        {
            LocalPointer<tester[]> ptr2(std::move(ptr));
        }
        EXPECT_EQ(4, destructorCounter);
    }
    EXPECT_EQ(4, destructorCounter);
    // Yes memory leak if the _EQ fails but hey, it won't be running 24/7 seven so we should be okay.
}

TEST(Pointer_LocalArrayPointer, TestPtrOperatorAccessor)
{
    static int opCounter = 0;
    struct tester
    {
        void Operation()
        {
            opCounter++;
        }
    };

    tester* data = new tester[2]();
    data[0] = tester();
    data[1] = tester();
    {
        LocalPointer<tester[]> ptr(data);
        ptr->Operation();
    }

    EXPECT_EQ(1, opCounter);
}

TEST(Pointer_LocalArrayPointer, TestDereferenceOperatorAccessor)
{
    static int opCounter = 0;
    struct tester
    {
        void Operation()
        {
            opCounter++;
        }
    };

    tester* data = new tester[2]();
    data[0] = tester();
    data[1] = tester();
    {
        LocalPointer<tester[]> ptr(data);
        (*ptr).Operation();
    }

    EXPECT_EQ(1, opCounter);
}

TEST(Pointer_LocalArrayPointer, TestGetMethodOperatorAccessor)
{
    static int opCounter = 0;
    struct tester
    {
        void Operation()
        {
            opCounter++;
        }
    };

    tester* data = new tester[2]();
    data[0] = tester();
    data[1] = tester();
    {
        LocalPointer<tester[]> ptr(data);
        ptr.Get()->Operation();
        (ptr.Get() + 1)->Operation();
    }

    EXPECT_EQ(2, opCounter);
}
