#include "pch.h"
#include "LocationViewModel.h"
#include "Location.h"

#include "App.h"

namespace winrt::GUI::implementation
{
    LocationViewModel::LocationViewModel()
    {
        //auto t = winrt::make<GUI::implementation::Location>(L"");
        auto l = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();

        winrt::GUI::implementation::Location t{};
        App::databaseService.insert<winrt::GUI::implementation::Location, Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable>>(t, l);

        if (l.Size() > 0) {
            OutputDebugString(L"YEAH");
        }

        auto locations = std::vector<winrt::GUI::Location>{
            winrt::make<GUI::implementation::Location>(L"Osten"),
            winrt::make<GUI::implementation::Location>(L"Hemmoor"),
            winrt::make<GUI::implementation::Location>(L"Hechthausen")
        };
        m_locations = winrt::single_threaded_observable_vector<Windows::Foundation::IInspectable>();

        for (auto &location : locations) {
            m_locations.Append(location);
        }
    }

    Windows::Foundation::Collections::IObservableVector<Windows::Foundation::IInspectable> LocationViewModel::Locations()
    {
        return m_locations;
    }
}
