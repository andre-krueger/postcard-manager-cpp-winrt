#pragma once

#include "Location.g.h"

namespace winrt::GUI::implementation
{
    struct Location : LocationT<Location>
    {
        Location() {}
        Location(hstring const& name);

        hstring Name();
        void Name(hstring const& value);
        winrt::event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;

    private:
        hstring m_name;
        // TODO: insert field for primary key
        winrt::event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}
