#include "searchresultwidget.h"
#include "ui_searchresultwidget.h"
#include "model/tracksearchresultmodel.h"
#include "api/searchresult.h"

SearchResultWidget::SearchResultWidget(SearchResult *searchResult, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResultWidget),
    m_trackSearchResultModel(new TrackSearchResultModel(searchResult))
{
    ui->setupUi(this);
    ui->listResult->setModel(m_trackSearchResultModel);
    connect(m_trackSearchResultModel, &TrackSearchResultModel::loading, ui->progressBar, &QProgressBar::show);
    connect(m_trackSearchResultModel, &TrackSearchResultModel::loaded, ui->progressBar, &QProgressBar::hide);
    connect(m_trackSearchResultModel, &TrackSearchResultModel::rowsInserted, ui->progressBar, &QProgressBar::hide);
    setWindowTitle("Resultados: " + searchResult->term());
}

SearchResultWidget::~SearchResultWidget()
{
    delete ui;
}
