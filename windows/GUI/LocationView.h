#pragma once

#include "LocationView.g.h"
#include "LocationViewModel.h"

namespace winrt::GUI::implementation
{
    struct LocationView : LocationViewT<LocationView>
    {
        LocationView();

        GUI::LocationViewModel LocationViewModel();

    private:
        GUI::LocationViewModel m_locationViewModel{ nullptr };
    };
}

namespace winrt::GUI::factory_implementation
{
    struct LocationView : LocationViewT<LocationView, implementation::LocationView>
    {
    };
}
