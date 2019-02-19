#pragma once

#include "LocationViewModel.g.h"

namespace winrt::GUI::implementation
{
    struct LocationViewModel : LocationViewModelT<LocationViewModel>
    {
        LocationViewModel();

        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> Locations();

    private:
        Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> m_locations;
    };
}
